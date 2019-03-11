/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:57 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:58:58 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			reg(t_file *x, char *buf, char *inst)
{
	int			i;
	int			nb;

	i = x->c;
	nb = 0;
	while (buf[i] && ft_isalnum(buf[i]))
	{
		i++;
		nb = (ft_isdigit(buf[i])) ? nb + 1 : nb;
		nb = (ft_isalpha(buf[i])) ? nb + 3 : nb;
	}
	if (nb == 0 || nb >= 3)
	{
		!x->name_err ? x->name_err = ft_strndup(&buf[x->c], i - x->c) : 0;
		save_err(x, x->c, 6);
	}
	else if (x->sep == 0)
	{
		fill_err_name(x, buf);
		save_err(x, x->c, 9);
	}
	else if (inst != NULL)
		save_err2(x, "register", inst, 20);
	x->c = --i;
	x->sep = 0;
}

int				dir2(t_file *x, char *buf, char *inst, int i)
{
	if (buf[i] == '-')
		i++;
	while (buf[i] && ft_isalnum(buf[i]) && buf[i] != '#' && buf[i] != ';')
	{
		if (ft_isalpha(buf[i]))
			break ;
		i++;
	}
	if (x->sep == 0)
	{
		!x->name_err ? x->name_err = ft_strndup(&buf[x->c], i - x->c) : 0;
		save_err(x, x->c, 10);
	}
	else if (inst != NULL)
		save_err2(x, "direct", inst, 20);
	return (i);
}

void			dir(t_file *x, char *buf, char *inst)
{
	int			i;

	i = x->c + 1;
	if (buf[i] == ':')
	{
		i++;
		while (buf[i] && buf[i] != '#' && buf[i] != ';'
			&& (ft_isalnum(buf[i]) || buf[i] == '_'))
			i++;
		fill_label(buf, x, i - x->c, 2);
		x->c = --i;
		x->sep = 0;
		if (inst != NULL)
			save_err2(x, "direct", inst, 20);
		return ;
	}
	else if (ft_isdigit(buf[i]) || buf[i] == '-')
		i = dir2(x, buf, inst, i);
	while (buf[i] && ft_isdigit(buf[i]) && buf[i] != '#')
		i++;
	x->c = --i;
	x->sep = 0;
}

static void		ind_complete(int *i, char *buf, char *inst, t_file *x)
{
	int			err;

	err = 0;
	while (buf[*i] && ft_isalnum(buf[*i]) && buf[*i] != '#')
	{
		if (ft_isalpha(buf[*i]))
			err = 1;
		*i = *i + 1;
	}
	if (err)
	{
		!x->name_err ? x->name_err = ft_strndup(&buf[x->c], *i - x->c) : 0;
		save_err(x, x->c, 6);
	}
	else if (x->sep == 0)
	{
		fill_err_name(x, buf);
		save_err(x, x->c, 11);
	}
	else if (inst != NULL)
		save_err2(x, "indirect", inst, 20);
}

void			ind(t_file *x, char *buf, char *inst)
{
	int			i;

	i = x->c;
	if (buf[i] == ':')
	{
		x->c--;
		i++;
		while (buf[i] && buf[i] != '#' && buf[i] != ';'
			&& (ft_isalnum(buf[i]) || buf[i] == '_'))
			i++;
		fill_label(buf, x, i - x->c, 2);
		x->c = --i;
		x->sep = 0;
		if (inst != NULL)
			save_err2(x, "indirect", inst, 20);
		return ;
	}
	if (buf[i] == '-')
		i++;
	ind_complete(&i, buf, inst, x);
	x->c = --i;
	x->sep = 0;
}
