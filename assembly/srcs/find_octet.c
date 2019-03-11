/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_octet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 11:25:17 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 17:21:01 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_arg(t_ligne **line, int fd, int nb, int i)
{
	write(fd, &nb, 1);
	if (i == 1)
	{
		i = ft_encoding(line);
		write(fd, &i, 1);
	}
	ft_write_arg(line, -1, fd);
	return (0);
}

static void		ft_find_label(t_ligne **line, int fd)
{
	ft_strcmp((*line)->instruct, "live") == 0 ? ft_arg(line, fd, 1, 0) : 0;
	ft_strcmp((*line)->instruct, "ld") == 0 ? ft_arg(line, fd, 2, 1) : 0;
	ft_strcmp((*line)->instruct, "st") == 0 ? ft_arg(line, fd, 3, 1) : 0;
	ft_strcmp((*line)->instruct, "add") == 0 ? ft_arg(line, fd, 4, 1) : 0;
	ft_strcmp((*line)->instruct, "sub") == 0 ? ft_arg(line, fd, 5, 1) : 0;
	ft_strcmp((*line)->instruct, "and") == 0 ? ft_arg(line, fd, 6, 1) : 0;
	ft_strcmp((*line)->instruct, "or") == 0 ? ft_arg(line, fd, 7, 1) : 0;
	ft_strcmp((*line)->instruct, "xor") == 0 ? ft_arg(line, fd, 8, 1) : 0;
	ft_strcmp((*line)->instruct, "zjmp") == 0 ? ft_arg(line, fd, 9, 0) : 0;
	ft_strcmp((*line)->instruct, "ldi") == 0 ? ft_arg(line, fd, 10, 1) : 0;
	ft_strcmp((*line)->instruct, "sti") == 0 ? ft_arg(line, fd, 11, 1) : 0;
	ft_strcmp((*line)->instruct, "fork") == 0 ? ft_arg(line, fd, 12, 0) : 0;
	ft_strcmp((*line)->instruct, "lld") == 0 ? ft_arg(line, fd, 13, 1) : 0;
	ft_strcmp((*line)->instruct, "lldi") == 0 ? ft_arg(line, fd, 14, 1) : 0;
	ft_strcmp((*line)->instruct, "lfork") == 0 ? ft_arg(line, fd, 15, 0) : 0;
	ft_strcmp((*line)->instruct, "aff") == 0 ? ft_arg(line, fd, 16, 1) : 0;
}

static t_ligne	*ft_free_line(t_ligne **line)
{
	t_ligne		*next;
	int			i;

	i = -1;
	while ((*line)->instruct[++i])
		(*line)->instruct[i] = '\0';
	next = (*line)->next;
	ft_strdel(&(*line)->arg);
	ft_strdel(&(*line)->label);
	ft_strdel(&(*line)->ligne);
	free(*line);
	return (next);
}

static void		ft_line_octet(t_ligne **line)
{
	int		count;

	count = 0;
	while ((*line))
	{
		count = count + (*line)->nb_loctet;
		(*line)->nb_octet_pos = count;
		(*line) = (*line)->next;
	}
}

void			find_octet(t_ligne **begin, int fd, t_header head)
{
	t_ligne		*line;

	line = *begin;
	ft_line_octet(&line);
	line = *begin;
	while (line != NULL)
	{
		ft_label(&line, *begin, 0);
		line = line->next;
	}
	line = *begin;
	if (line)
		while (line->next != NULL)
			line = line->next;
	ft_affiche_header(head, fd, line, 0);
	line = *begin;
	while (line != NULL)
	{
		ft_find_label(&line, fd);
		line = ft_free_line(&line);
	}
	close(fd);
}
