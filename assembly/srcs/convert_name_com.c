/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_name_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:37:24 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/13 16:09:25 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			ft_nb_octet(char *str, t_ligne **nline)
{
	if (ft_strcmp(str, "live") == 0
			|| ft_strcmp(str, "add") == 0 || ft_strcmp(str, "sub") == 0)
		(*nline)->nb_loctet = 5;
	else if (ft_strcmp(str, "zjmp") == 0
			|| ft_strcmp(str, "fork") == 0 || ft_strcmp(str, "lfork") == 0)
		(*nline)->nb_loctet = 3;
	else if (ft_strcmp(str, "ld") == 0 || ft_strcmp(str, "lld") == 0)
		(*nline)->nb_loctet = (ft_is_dir((*nline)->arg) == 1) ? 5 : 7;
	else if (ft_strcmp(str, "sti") == 0
			|| ft_strcmp(str, "lldi") == 0 || ft_strcmp(str, "ldi") == 0)
		(*nline)->nb_loctet = find_size_2(nline);
	else if (ft_strcmp(str, "xor") == 0
			|| ft_strcmp(str, "or") == 0 || ft_strcmp(str, "and") == 0)
		(*nline)->nb_loctet = find_size(nline);
	else if (ft_strcmp(str, "aff") == 0)
		(*nline)->nb_loctet = 3;
	else
		(*nline)->nb_loctet = find_size(nline);
}

static	char	*find_name(char *name)
{
	int			i;
	char		*str;

	i = 0;
	while (name[i])
		i++;
	while (name[i] != '.' && i > 0)
		i--;
	if ((str = ft_strnew((size_t)i + 4)) == NULL)
		return (NULL);
	str = ft_strncpy(str, name, (size_t)i);
	str = ft_strcat(str, ".cor");
	return (str);
}

void			convert_name_com(char **str, char *name)
{
	t_ligne		*begin;
	char		*new_n;
	t_header	head;

	if ((new_n = find_name(name)) == NULL)
		return ;
	begin = initialize_struct(str + 2, 0);
	head = initialize_header(str);
	find_octet(&begin, open(new_n, O_WRONLY | O_TRUNC | O_CREAT, 0600), head);
	ft_putstr("Writing output program to ");
	ft_putendl(new_n);
	ft_strdel(&new_n);
}
