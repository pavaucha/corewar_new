/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:59:01 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 19:56:32 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	**fill_file(char **file, int i)
{
	int		quote;
	int		j;
	char	**s;

	if (!(s = (char**)ft_memalloc(sizeof(char*)
			* ((unsigned long)ft_tablen(file) + 1))))
		return (NULL);
	while (file[++i])
	{
		j = 0;
		quote = 0;
		while (file[i][j++])
		{
			if (file[i][j] == '"')
				quote++;
			if ((file[i][j] == '#' || file[i][j] == ';') && quote != 1)
				while (file[i][j])
					file[i][j++] = ' ';
		}
		if (!(s[i] = ft_strtrim(file[i])))
			return (NULL);
	}
	s[i] = 0;
	return (s);
}

int		check_file(t_file *x, char **buf, int *i, int ret)
{
	int ret2;

	if (ret == 2)
		x->endline = 1;
	x->l++;
	reset_var(x, i);
	if (ret == -1 || (ret2 = check_line(buf, x)) == -1)
	{
		if (ret == -1)
			save_err(x, x->c, 14);
		ft_strdel(buf);
		return (ret == -1 || x->err == 15 ? print_err(x, x->err) : -1);
	}
	while ((*buf)[(*i)] != '\0' && ft_isblank((*buf)[(*i)]))
		(*i)++;
	if ((!(*buf)[*i] || (*buf)[*i] == '#' || (*buf)[*i] == ';' || x->err == 18)
		&& ret2 != 1)
	{
		ft_strdel(buf);
		return (1);
	}
	return (0);
}

int		no_newline(t_file *x)
{
	if (!x->body)
		return (0);
	if (!(x->err >= 5 && x->err <= 11) && x->err != 2 && x->err != 4
		&& x->err != 13 && x->err != 14 && !x->endline && x->err != 17
		&& x->err != 18)
	{
		ft_putstr_fd("Syntax error - unexpected end of input ", 2);
		ft_putstr_fd("(Perhaps you forgot to end with a newline ?)\n", 2);
		return (-1);
	}
	return (0);
}

int		err(t_file *x, int ret, char *buf)
{
	char	**file;

	if (ret == 0 || buf)
		ft_strdel(&buf);
	if (no_newline(x) == -1)
		return (-1);
	fill_label(NULL, x, 0, 3);
	if (ret == 0 && x->l == -1)
		save_err(x, x->c, 14);
	if (x->err == 18 && !x->body)
		save_err(x, 0, 15);
	if (x->err && x->err != 18 && x->err != 19)
		return (print_err(x, x->err));
	if (!(file = ft_strsplit(x->s, '\n')))
		return (-1);
	if (!(x->file = fill_file(file, -1)))
		return (-1);
	ft_strdel(&x->s);
	ft_strdel_tab(&file);
	if (x->body == 0 || x->file[2] == NULL)
	{
		save_err(x, 0, 15);
		return (print_err(x, x->err));
	}
	return (0);
}

int		parse_file(t_file *x, char *buf)
{
	int		ret;
	int		ret2;
	int		i;

	while ((ret = get_next_line(x->fd, &buf)) != 0)
	{
		if (x->l == 0 && buf[0] != '\0' && !ft_isblank(buf[0]) && buf[0] != '#'
			&& buf[0] != '\n' && buf[0] != '.' && buf[0] != ';')
			break ;
		if ((ret2 = check_file(x, &buf, &i, ret)) == -1)
			return (fill_exec_label(NULL, x, 0, 1));
		if (ret2 == 1 && x->l != 1)
			continue ;
		if (!x->err)
			if (!(x->s = ft_strjoin_char(x->s, x->body ? buf : "", '\n')))
				return (-1);
		ft_strdel(&buf);
	}
	if (err(x, ret, buf) == -1)
	{
		ft_strdel(&x->s);
		return (-1);
	}
	return (0);
}
