/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:57:24 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 18:21:06 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	inst_or(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 2) == 1)
		return (0);
	while (buf[x->c])
	{
		if (buf[x->c] == '#' || buf[x->c] == ';')
			break ;
		else if (buf[x->c] == '"')
			save_err(x, x->c, 17);
		else if (buf[x->c] == ',')
			separator(x);
		else if (buf[x->c] == '%')
			x->param <= 2 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "or");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param <= 2 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "or");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "or");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "or", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_xor(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 3) == 1)
		return (0);
	while (buf[x->c])
	{
		if (buf[x->c] == '#' || buf[x->c] == ';')
			break ;
		else if (buf[x->c] == '"')
			save_err(x, x->c, 17);
		else if (buf[x->c] == ',')
			separator(x);
		else if (buf[x->c] == '%')
			x->param <= 2 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "xor");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param <= 2 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "xor");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "xor");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "xor", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_zjmp(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 4) == 1)
		return (0);
	while (buf[x->c])
	{
		if (buf[x->c] == '#' || buf[x->c] == ';')
			break ;
		else if (buf[x->c] == '"')
			save_err(x, x->c, 17);
		else if (buf[x->c] == ',')
			separator(x);
		else if (buf[x->c] == '%')
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "zjmp");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "zjmp");
		else if (buf[x->c] == 'r')
			reg(x, buf, "zjmp");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_ldi(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 3) == 1)
		return (0);
	while (buf[x->c])
	{
		if (buf[x->c] == '#' || buf[x->c] == ';')
			break ;
		else if (buf[x->c] == '"')
			save_err(x, x->c, 17);
		else if (buf[x->c] == ',')
			separator(x);
		else if (buf[x->c] == '%')
			x->param <= 2 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "ldi");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 1 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "ldi");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "ldi");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "ldi", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_sti(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 3) == 1)
		return (0);
	while (buf[x->c])
	{
		if (buf[x->c] == '#' || buf[x->c] == ';')
			break ;
		else if (buf[x->c] == '"')
			save_err(x, x->c, 17);
		else if (buf[x->c] == ',')
			separator(x);
		else if (buf[x->c] == '%')
			x->param == 2 || x->param == 3 ?
			dir(x, buf, NULL) : dir(x, buf, "sti");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 2 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "sti");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "sti");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "sti", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}
