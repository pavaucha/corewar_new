/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_inst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:59:19 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:59:20 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	inst_space(t_file *x, char *buf)
{
	if (buf[x->c] == '#')
		return (1);
	else if (buf[x->c] == ',')
	{
		separator(x);
		return (0);
	}
	else if (buf[x->c] == '%')
	{
		dir(x, buf, NULL);
		return (0);
	}
	else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
	{
		ind(x, buf, NULL);
		return (0);
	}
	else if (buf[x->c] == 'r')
	{
		reg(x, buf, NULL);
		return (0);
	}
	return (-1);
}

int			inst_wrong(t_file *x, char *buf)
{
	if (buf[x->c] == 'r' || ft_isdigit(buf[x->c])
		|| buf[x->c] == '%' || buf[x->c] == '-' || buf[x->c] == ':')
		x->sep = 0;
	while (buf[x->c])
	{
		if (inst_space(x, buf) == 1)
			break ;
		else if (inst_space(x, buf) == 0)
			x->c = x->c + 1 - 1;
		else if (ft_isalpha(buf[x->c]) || buf[x->c] == '"')
			other_wrong(x, buf, 6);
		if (buf[x->c])
			x->c++;
	}
	if ((!x->err || x->err >= 20) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int			inst_wrong2(t_file *x, char *buf)
{
	if (buf[x->c] == 'r' || ft_isdigit(buf[x->c])
		|| buf[x->c] == '%' || buf[x->c] == '-' || buf[x->c] == ':')
		x->sep = 0;
	while (buf[x->c])
	{
		if (inst_space(x, buf) == 1)
			break ;
		else if (inst_space(x, buf) == 0)
			x->c = x->c + 1 - 1;
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 13);
		if (buf[x->c])
			x->c++;
	}
	if ((!x->err || x->err >= 20) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}
