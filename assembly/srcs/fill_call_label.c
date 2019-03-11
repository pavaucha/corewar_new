/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_call_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:21 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:58:22 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		fill_call_label_2(t_file *x, t_check_label *new)
{
	t_check_label *current;

	current = x->label;
	while (current->next)
	{
		if (!ft_strcmp(current->name, new->name))
		{
			ft_strdel(&new->name);
			free(new);
			return (0);
		}
		current = current->next;
	}
	if (!ft_strcmp(current->name, new->name))
	{
		ft_strdel(&new->name);
		free(new);
		return (0);
	}
	current->next = new;
	return (0);
}

int				fill_call_label(char *buf, t_file *x, int len)
{
	t_check_label *new;

	if (x->err)
		return (0);
	if (!(new = (t_check_label*)ft_memalloc(sizeof(t_check_label))))
		return (-1);
	new->l = x->l;
	new->c = x->c;
	if (!(new->name = ft_strndup(&buf[x->c + 2], len - 2)))
	{
		new->name = NULL;
		return (-1);
	}
	new->next = NULL;
	if (x->label == NULL)
		x->label = new;
	else
		fill_call_label_2(x, new);
	return (0);
}
