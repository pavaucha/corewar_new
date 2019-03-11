/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:59:23 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:59:24 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	other_wrong(t_file *x, char *buf, int c)
{
	int save;

	save = x->c;
	while (buf[x->c] && ft_isalnum(buf[x->c]))
	{
		if (buf[x->c] == ',' || buf[x->c] == '#' || buf[x->c] == '%')
			break ;
		x->c++;
	}
	if (!x->name_err)
		if (!(x->name_err = ft_strndup(&buf[save], x->c - save)))
			x->name_err = NULL;
	save_err(x, save, buf[x->c] != ':' ? c : 16);
}
