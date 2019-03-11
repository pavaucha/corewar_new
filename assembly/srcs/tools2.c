/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:59:12 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:59:14 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		free_parsing2(t_file *x)
{
	if (x->name_err)
		ft_strdel(&x->name_err);
	if (x->file)
		ft_strdel_tab(&x->file);
	if (x->name_f)
		ft_strdel(&x->name_f);
	if (x->lab)
		ft_strdel_tab(&x->lab);
	if (x->s)
		ft_strdel(&x->s);
	if (x->fd > 0)
		close(x->fd);
}

int				free_parsing(t_file *x, int c)
{
	t_check_label	*tmp;
	char			*buf;

	if (c == 1)
		while ((get_next_line(x->fd, &buf)) > 0)
			ft_strdel(&buf);
	while (x->label)
	{
		tmp = x->label->next;
		if (x->label->name != NULL)
			ft_strdel(&x->label->name);
		free(x->label);
		x->label = tmp;
	}
	free_parsing2(x);
	return (-1);
}

size_t			ft_strlen_custom(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*(s + i) != '\0' && *(s + i) != '%' && ft_isblank(*(s + i)) == 0)
		i++;
	return (i);
}
