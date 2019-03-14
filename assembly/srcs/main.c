/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:58:51 by mavui             #+#    #+#             */
/*   Updated: 2019/03/14 14:55:57 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				usage(t_file *x, char *av)
{
	ft_printf("Usage: %s <sourcefile.s>\n", av);
	return (free_parsing(x, 0));
}

static int		valide_file(t_file *x, int ac, char **av)
{
	if (ac == 1)
		return (usage(x, av[0]));
	if (!(x->name_f = ft_strdup(av[ac - 1])))
		return (0);
	if ((x->fd = open(av[ac - 1], O_RDONLY)) < 0)
	{
		ft_printf("Can't read source file %s\n", av[ac - 1]);
		return (free_parsing(x, 0));
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_file	x;

	if ((init_var(&x)) == -1)
		return (1);
	if (valide_file(&x, ac, av) == -1)
		return (1);
	if ((parse_file(&x, NULL)) == -1)
		return (free_parsing(&x, 1));
	convert_name_com(x.file, x.name_f);
	free_parsing(&x, 0);
	while (1);
	return (0);
}
