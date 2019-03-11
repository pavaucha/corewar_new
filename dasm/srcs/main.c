/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:32:20 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 14:04:14 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

static void		ft_initialize_strcut(t_champ *champ)
{
	champ->len = 0;
	ft_bzero(champ->magic, 4);
	ft_bzero(champ->instructions, CHAMP_MAX_SIZE);
	ft_bzero(champ->name, PROG_NAME_LEN);
	ft_bzero(champ->comment, COMMENT_LEN);
}

static char		*open_file(char *name)
{
	int		i;
	char	*str;

	i = 0;
	while (name[i])
		i++;
	while (name[i] != '.' && i > 0)
		i--;
	if ((str = ft_strnew((size_t)i + 3)) == NULL)
		return (NULL);
	str = ft_strncpy(str, name, (size_t)i);
	str = ft_strcat(str, ".rev");
	return (str);
}

int				main(int ac, char **av)
{
	t_champ		champ;
	char		*str;

	ft_initialize_strcut(&champ);
	if (ac != 2)
	{
		ft_printf("Please enter a champ to this format\n");
		ft_printf("		./reverse_cor <#####.cor>\n");
		return (1);
	}
	if (parsing_champ(av[1], &champ) != 1)
		return (1);
	if ((str = (open_file(av[1]))) == NULL)
	{
		ft_strdel(&str);
		return (ft_error(7));
	}
	if (complete_file(str, champ) != 0)
	{
		ft_strdel(&str);
		return (-1);
	}
	ft_printf("Writing output program to %s\n", str);
	ft_strdel(&str);
	return (1);
}
