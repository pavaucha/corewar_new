/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:32:38 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 11:29:54 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

static int		open_read_file(char *name, t_champ *champ)
{
	int			fd;

	if ((fd = open(name, O_RDONLY)) <= 0)
		return (-1);
	if (complete(fd, champ) != 0)
	{
		close(fd);
		return (-1);
	}
	return (1);
}

int				parsing_champ(char *name, t_champ *champ)
{
	if (open_read_file(name, champ) == -1)
		return (-1);
	return (1);
}
