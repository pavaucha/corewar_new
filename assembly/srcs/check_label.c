/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:57:38 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 18:17:55 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		fill_name_label(t_file *x, char **name, char *s)
{
	if ((*name) == NULL)
	{
		if (!((*name) = ft_strnew(0)))
		{
			ft_strdel(&s);
			return (-1);
		}
	}
	if (x->err != 18 && !((*name) = ft_strjoin_char((*name), s, '\n')))
	{
		ft_strdel(&s);
		return (-1);
	}
	ft_strdel(&s);
	return (0);
}

static int		fill_exec_label_2(char *name, t_file *x)
{
	if (!(x->lab = ft_strsplit(name, '\n')))
	{
		if (!(x->lab = (char**)ft_memalloc(sizeof(char*))))
			return (-1);
		x->lab[0] = 0;
		return (0);
	}
	ft_strdel(&name);
	return (0);
}

int				fill_exec_label(char *buf, t_file *x, int len, int c)
{
	static char *name = NULL;
	char		*s;

	s = NULL;
	if (x->err && x->err != 18 && c == 1)
	{
		ft_strdel(&name);
		return (-1);
	}
	if (buf != NULL)
		if (!(s = ft_strndup(&buf[x->c], len)))
			return (-1);
	if (c == 1 && fill_name_label(x, &name, s) == -1)
		return (-1);
	else if (c == 3 && fill_exec_label_2(name, x) == -1)
		return (-1);
	return (0);
}

int				fill_label(char *buf, t_file *x, int len, int c)
{
	t_check_label	*cur;
	int				i;

	if (c == 1 || c == 3)
		fill_exec_label(buf, x, len, c);
	else if (c == 2)
		fill_call_label(buf, x, len);
	if (c == 3)
	{
		cur = x->label;
		while (cur)
		{
			i = -1;
			while (x->lab[++i])
				if (!ft_strcmp(cur->name, x->lab[i]))
					break ;
			if (x->lab[i] == NULL)
				return (label_err(x, cur));
			cur = cur->next;
		}
	}
	return (0);
}

int				check_label(char *buf, t_file *x)
{
	int i;

	i = x->c;
	while (buf[i] && (ft_isalnum(buf[i]) || buf[i] == '_'))
		i++;
	if (buf[i] == ':')
	{
		fill_label(buf, x, i++ - x->c, 1);
		while (buf[i] && ft_isblank(buf[i]))
			i++;
		x->c = i;
		if (buf[x->c] == '\0' || buf[x->c] == '#' || buf[x->c] == ';')
		{
			x->body = 1;
			return (1);
		}
	}
	return (0);
}
