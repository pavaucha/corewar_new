/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:57:31 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 18:21:26 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	inst_fork(char *buf, t_file *x)
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
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "fork");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "fork");
		else if (buf[x->c] == 'r')
			reg(x, buf, "fork");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_lld(char *buf, t_file *x)
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
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "lld");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 1 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "lld");
		else if (buf[x->c] == 'r')
			x->param == 2 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "lld");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 2 ? save_err2(x, NULL, "lld", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_lldi(char *buf, t_file *x)
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
			x->param <= 2 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "lldi");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			x->param == 1 && x->sep ? ind(x, buf, NULL) : ind(x, buf, "lldi");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "lldi");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "lldi", 21) : 0;
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_lfork(char *buf, t_file *x)
{
	if (no_params(x, buf, x->c + 5) == 1)
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
			x->param == 1 && x->sep ? dir(x, buf, NULL) : dir(x, buf, "lfork");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "lfork");
		else if (buf[x->c] == 'r')
			reg(x, buf, "lfork");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}

int	inst_aff(char *buf, t_file *x)
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
			dir(x, buf, "aff");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "aff");
		else if (buf[x->c] == 'r')
			x->param == 1 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "aff");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	if ((!x->err || x->err > 19) && x->sep)
		endline_err(x, (int)ft_strlen(buf), 1);
	return (0);
}
