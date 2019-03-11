/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:15 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:58:16 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fill_err_name(t_file *x, char *buf)
{
	int i;

	if (!x->err || x->err >= 20)
	{
		i = x->c;
		if (buf[i] == '%')
			i++;
		while (buf[i] && !ft_isblank(buf[i]) && buf[i] != ','
			&& buf[i] != '#' && buf[i] != '%')
			i++;
		if (!(x->name_err = ft_strndup(&buf[x->c], i - x->c)))
			x->name_err = NULL;
	}
}

int		save_err(t_file *x, int col, int c)
{
	if (!x->err || (x->err != 5 && c == 5) || x->err >= 20
		|| (c == 7 && x->err == 8 && x->line_err == x->l + 1))
	{
		if (c == 14)
		{
			x->col_err = 1;
			x->line_err = 1;
			x->err = c;
		}
		else
		{
			x->col_err = col + 1;
			x->line_err = x->l + 1;
			x->err = c;
		}
	}
	if (x->err == 18)
	{
		x->col_err = col + 1;
		x->line_err = x->l + 1;
		x->err = c;
	}
	return (c == 5 || c == 14 ? -1 : 0);
}

int		save_err2(t_file *x, char *type, char *inst, int c)
{
	if (!x->err)
	{
		x->err = c;
		if (inst)
			ft_strcpy(x->inst_err, inst);
		if (c == 21)
			return (0);
		if (type)
			ft_strcpy(x->type_err, type);
		x->param_err = x->param - 1;
	}
	return (0);
}

int		endline_err(t_file *x, int col, int c)
{
	static int check = 1;

	x->err = 8;
	if (c == 2)
		check = 2;
	else if (check != 2)
	{
		x->col_err = col + 1;
		x->line_err = x->l + 1;
	}
	return (0);
}

int		label_err(t_file *x, t_check_label *lab)
{
	if (!x->err || x->err == 19)
	{
		x->err = 12;
		x->col_err = lab->c + 1;
		x->line_err = lab->l + 1;
		if (!(x->name_err = ft_strdup(lab->name)))
			x->name_err = NULL;
	}
	return (0);
}
