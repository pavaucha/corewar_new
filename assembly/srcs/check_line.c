/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:57:55 by mavui             #+#    #+#             */
/*   Updated: 2019/02/27 18:16:11 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		inst_add(char *buf, t_file *x)
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
			dir(x, buf, "add");
		else if (ft_isdigit(buf[x->c]) || buf[x->c] == '-' || buf[x->c] == ':')
			ind(x, buf, "add");
		else if (buf[x->c] == 'r')
			x->param <= 3 && x->sep ? reg(x, buf, NULL) : reg(x, buf, "add");
		else if (ft_isalpha(buf[x->c]))
			other_wrong(x, buf, 6);
		buf[x->c] ? x->c++ : 0;
	}
	!x->err && x->param < 3 ? save_err2(x, NULL, "add", 21) : 0;
	(!x->err || x->err > 19) && x->sep
			? endline_err(x, (int)ft_strlen(buf), 1) : 0;
	return (0);
}

void	check_inst(char *buf, t_file *x, char *inst)
{
	!ft_strcmp(inst, "add") ? inst_add(buf, x) : 0;
	!ft_strcmp(inst, "aff") ? inst_aff(buf, x) : 0;
	!ft_strcmp(inst, "and") ? inst_and(buf, x) : 0;
	!ft_strcmp(inst, "fork") ? inst_fork(buf, x) : 0;
	!ft_strcmp(inst, "ldi") ? inst_ldi(buf, x) : 0;
	!ft_strcmp(inst, "ld") ? inst_ld(buf, x) : 0;
	!ft_strcmp(inst, "lfork") ? inst_lfork(buf, x) : 0;
	!ft_strcmp(inst, "live") ? inst_live(buf, x) : 0;
	!ft_strcmp(inst, "lld") ? inst_lld(buf, x) : 0;
	!ft_strcmp(inst, "lldi") ? inst_lldi(buf, x) : 0;
	!ft_strcmp(inst, "or") ? inst_or(buf, x) : 0;
	!ft_strcmp(inst, "sti") ? inst_sti(buf, x) : 0;
	!ft_strcmp(inst, "st") ? inst_st(buf, x) : 0;
	!ft_strcmp(inst, "sub") ? inst_sub(buf, x) : 0;
	!ft_strcmp(inst, "xor") ? inst_xor(buf, x) : 0;
	!ft_strcmp(inst, "zjmp") ? inst_zjmp(buf, x) : 0;
	if (x->inst == 0)
	{
		if (x->err == 18)
			x->err = 0;
		inst_wrong2(x, buf);
	}
}

int		body(char *buf, t_file *x)
{
	char *inst;

	if (check_label(buf, x) == 1)
		return (0);
	if (x->name == 0 || x->comment == 0)
	{
		inst_wrong(x, buf);
		return (0);
	}
	if (char_err(buf, x) == -1)
		return (print_err(x, x->err));
	if (x->err == 18 && x->body)
		return (0);
	if (!(inst = ft_strndup(&buf[x->c], (int)ft_strlen_custom(&buf[x->c]))))
		return (-1);
	check_inst(buf, x, inst);
	ft_strdel(&inst);
	x->body = 1;
	return (0);
}

int		endline(t_file *x, char *buf)
{
	while (buf[x->c] && ft_isblank(buf[x->c]))
		x->c++;
	if (buf[x->c] == '\0' || buf[x->c] == '#' || buf[x->c] == ';')
	{
		if (x->err == 8)
			endline_err(x, (int)ft_strlen(buf), 1);
		return (1);
	}
	if (x->err == 8)
		endline_err(x, x->c, 2);
	return (0);
}

int		check_line(char **buf, t_file *x)
{
	if (endline(x, (*buf)) == 1)
		return (0);
	if (lex_err((*buf), x->c) && (*buf)[x->c] != '.')
		save_err(x, x->c, 5);
	else if ((*buf)[x->c] == '.' && x->err != 18)
	{
		if (header(buf, x, 0) == -1)
			return (-1);
		return (1);
	}
	else
	{
		if ((body(*buf, x)) == -1)
			return (-1);
	}
	return (0);
}
