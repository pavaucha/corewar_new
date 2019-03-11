/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:59:07 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:59:08 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		separator(t_file *x)
{
	if (x->sep == 1)
		save_err(x, x->c, 7);
	x->sep = 1;
	!x->err ? x->param++ : 0;
	return (0);
}

int		init_var(t_file *x)
{
	if (!(x->s = ft_strnew(0)))
		return (-1);
	x->fd = 0;
	x->body = 0;
	x->l = -1;
	x->c = 0;
	x->name = 0;
	x->comment = 0;
	x->err = 0;
	x->col_err = 0;
	x->line_err = 0;
	x->name_f = NULL;
	x->name_err = NULL;
	x->lab = NULL;
	x->label = NULL;
	x->file = NULL;
	x->endline = 0;
	ft_memset(x->inst_err, 0, 5);
	ft_memset(x->type_err, 0, 8);
	return (0);
}

void	reset_var(t_file *x, int *i)
{
	x->c = 0;
	x->inst = 0;
	x->param = 1;
	x->sep = 1;
	*i = 0;
}

int		no_params(t_file *x, char *buf, int i)
{
	if (buf[i] != '%' && ((buf[i]) == '\0' || !ft_isblank(buf[i])))
	{
		save_err(x, (int)ft_strlen(buf), 8);
		return (1);
	}
	x->c = i;
	x->inst = 1;
	return (0);
}

int		fill_file2(t_file *x, int c, char *s2, int j)
{
	if (c == 1)
	{
		if (j > 128)
			return (save_err(x, 0, 1));
		if (!(x->s = ft_strjoin_char(x->s, ".name ", '"')))
			return (-1);
		if (!(x->s = ft_strjoin_char(x->s, s2, '"')))
			return (-1);
	}
	else if (c == 2)
	{
		if (j > 2048)
			return (save_err(x, 0, 3));
		if (!(x->s = ft_strjoin_char(x->s, ".comment ", '"')))
			return (-1);
		if (!(x->s = ft_strjoin_char(x->s, s2, '"')))
			return (-1);
	}
	return (1);
}
