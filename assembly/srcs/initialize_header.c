/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 14:10:13 by pavaucha          #+#    #+#             */
/*   Updated: 2019/02/12 20:58:42 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		complete_init_head(char **str, t_header *head)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str[0][j] != '"')
		j++;
	while (str[0][++j] != '"')
		head->comment[++i] = str[0][j];
	head->comment[++i] = '\0';
	i = -1;
	j = 0;
	while (str[1][j] != '"')
		j++;
	while (str[1][++j] != '"')
		head->prog_name[++i] = str[1][j];
	head->prog_name[++i] = '\0';
}

t_header		initialize_header(char **str)
{
	int			i;
	int			j;
	t_header	head;

	i = -1;
	j = 0;
	if (str[0][1] == 'n')
	{
		while (str[0][j] != '"')
			j++;
		while (str[0][++j] != '"')
			head.prog_name[++i] = str[0][j];
		head.prog_name[++i] = '\0';
		i = -1;
		j = 0;
		while (str[1][j] != '"')
			j++;
		while (str[1][++j] != '"')
			head.comment[++i] = str[1][j];
		head.comment[++i] = '\0';
	}
	else
		complete_init_head(str, &head);
	return (head);
}
