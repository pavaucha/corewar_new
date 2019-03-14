/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:57:16 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 18:20:15 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	inst_live(char *buf, t_file *x)
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
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "live");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "live");
		else if (buf[x->c] == 'r')
			reg(x, buf, "live");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_ld(char *buf, t_file *x)
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
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "ld");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 1 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "ld");
		else if (buf[x->c] == 'r')
			x->param == 2 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "ld");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 2 ? save_err2(x, NULL, "ld", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_st(char *buf, t_file *x)
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
			dir(x, buf, "st");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 2 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "st");
		else if (buf[x->c] == 'r')
			x->param <= 2 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "st");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 2 ? save_err2(x, NULL, "st", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_sub(char *buf, t_file *x)
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
			dir(x, buf, "sub");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "sub");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "sub");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "sub", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_and(char *buf, t_file *x)
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
			x->param <= 2 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "and");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param <= 2 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "and");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "and");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "and", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}
