/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 16:57:22 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 17:39:25 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				find_size_2(t_ligne **line)
{
	int			i;
	int			count;
	char		**str;
	int			j;

	count = 0;
	i = -1;
	if ((str = ft_strsplit((*line)->arg, ',')) == NULL)
		return (0);
	while (str[++i])
	{
		j = 0;
		while (ft_isblank(str[i][j]))
			j++;
		if (str[i][j] == 'r')
			count = count + 1;
		else
			count = count + 2;
	}
	ft_strdel_tab(&str);
	return (count + 2);
}

int				find_size(t_ligne **line)
{
	int			i;
	int			count;
	char		**str;
	int			j;

	count = 0;
	i = -1;
	if ((str = ft_strsplit((*line)->arg, ',')) == NULL)
		return (0);
	while (str[++i])
	{
		j = 0;
		while (ft_isblank(str[i][j]))
			j++;
		if (str[i][j] == 'r')
			count = count + 1;
		else if (str[i][j] == '%')
			count = count + 4;
		else
			count = count + 2;
	}
	ft_strdel_tab(&str);
	return (count + 2);
}

int				ft_is_dir(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			return (0);
		i++;
	}
	return (1);
}

static int		ft_slabel(t_ligne *tmp, int count, t_ligne **line, char *str)
{
	t_ligne *tmp_2;

	if (!tmp)
		return (0);
	tmp_2 = (tmp->nb_octet_pos > (*line)->nb_octet_pos) ? *line : tmp->next;
	if (tmp->nb_octet_pos > (*line)->nb_octet_pos)
	{
		while (ft_strcmp(tmp_2->label, str) != 0)
		{
			count = count + tmp_2->nb_loctet;
			tmp_2 = tmp_2->next;
		}
	}
	else if (tmp->nb_octet_pos < (*line)->nb_octet_pos)
	{
		count = count - tmp->nb_loctet;
		while (tmp_2 && tmp_2->nb_octet_pos != (*line)->nb_octet_pos)
		{
			count = count - tmp_2->nb_loctet;
			tmp_2 = tmp_2->next;
		}
	}
	else if (tmp->nb_octet_pos == (*line)->nb_octet_pos)
		return ((*line)->nb_octet_pos);
	return (count);
}

void			ft_label(t_ligne **line, t_ligne *begin, int j)
{
	int			i;
	char		*str;
	t_ligne		*tmp;

	i = -1;
	if ((*line)->arg == NULL)
		return ;
	while ((*line)->arg[++i] != '\0')
	{
		if ((*line)->arg[i] == ':')
		{
			tmp = begin;
			if ((str = ft_strsub((*line)->arg + i + 1, 0,
					(size_t)ft_islabel((*line)->arg + i + 1))) == NULL)
				return ;
			while (tmp != NULL && ft_strcmp(tmp->label, str) != 0)
				tmp = tmp->next;
			(*line)->pos[j] = ft_slabel(tmp, 0, line, str);
			j++;
			ft_strdel(&str);
		}
	}
	(*line)->pos[j] = 0;
}
