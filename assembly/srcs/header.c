/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:40 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:58:41 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_header2(char *buf, t_file *x)
{
	int save_col;

	while (buf[x->c] && ft_isblank(buf[x->c]))
		x->c++;
	if (buf[x->c] == '\0' || buf[x->c] == '#' || buf[x->c] == ';')
		return ;
	save_col = x->c;
	if (char_err(&buf[x->c], x) == -1)
	{
		x->col_err += save_col;
		return ;
	}
	!x->err ? inst_wrong(x, buf) : 0;
}

int		quote_arg(t_file *x, char **buf, char *s2, int *j)
{
	static int ret = -1;

	if ((*buf)[x->c] == '"' || (*j) > 2048 || ret == 0)
	{
		s2[(*j)] = '\0';
		return (1);
	}
	else if ((*buf)[x->c] == '\0')
	{
		s2[(*j)++] = 127;
		ft_strdel(buf);
		if ((ret = ft_read(x->fd, buf)) == -1 || (*buf) == NULL)
		{
			x->l -= 1;
			return (-1);
		}
		ret != 0 ? x->l++ : 0;
		x->c = 0;
	}
	else
		s2[(*j)++] = (*buf)[x->c++];
	return (0);
}

int		before_quote(t_file *x, char *buf, int c)
{
	int i;

	i = (c == 1 ? x->c + 5 : x->c + 8);
	while (buf[i] && buf[i] != '"')
	{
		if (!ft_isblank(buf[i]))
		{
			x->c = i;
			if (!ft_isdigit(buf[i]) && !(buf[i] >= 'a' && buf[i] <= 'z'))
				return (char_err(buf, x));
			!x->err ? inst_wrong(x, buf) : 0;
		}
		else if (buf[i] == '#')
			return (-1);
		i++;
	}
	x->c = i;
	return (0);
}

int		quote(t_file *x, char **buf, int c)
{
	char	s2[2050];
	int		j;
	int		ret;

	j = 0;
	if (before_quote(x, (*buf), c) == -1)
		return (0);
	if ((*buf)[x->c] == '\0')
		return (save_err(x, x->c, 8));
	x->c++;
	while ((ret = quote_arg(x, buf, s2, &j)) != 1 && ret != -1)
		continue ;
	if (ret == -1)
	{
		save_err(x, x->c, 15);
		return (-1);
	}
	if (fill_file2(x, c, s2, j) == 0)
		return (0);
	if ((*buf)[x->c] != '"')
		save_err(x, 0, 15);
	if ((*buf)[++x->c] != '\0')
		check_header2((*buf), x);
	return (0);
}

int		header(char **buf, t_file *x, int ret)
{
	if (!ft_strncmp(&((*buf)[x->c]), ".name", 5))
	{
		x->name++;
		if (x->name > 1 && !x->body)
			return (save_err(x, x->c, 2));
		else if (x->name > 1 && x->body)
			!x->err ? x->err = 19 : 0;
		else
			ret = quote(x, buf, 1);
	}
	else if (!ft_strncmp(&((*buf)[x->c]), ".comment", 8))
	{
		x->comment++;
		if (x->comment > 1 && !x->body)
			return (save_err(x, x->c, 4));
		else if (x->comment > 1 && x->body)
			!x->err ? x->err = 19 : 0;
		else
			ret = quote(x, buf, 2);
	}
	else
		save_err(x, x->c, 5);
	return (ret == 0 ? 0 : -1);
}
