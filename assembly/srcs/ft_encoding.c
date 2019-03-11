/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_encoding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:27:55 by pavaucha          #+#    #+#             */
/*   Updated: 2018/11/27 21:22:10 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	char	*ft_encoding_suite(char **str, int j, int i)
{
	char		*new;
	int			k;

	if ((new = ft_strnew_c(7, '0')) == NULL)
		return (NULL);
	while (str[++i])
	{
		k = 0;
		while (ft_isblank(str[i][k]))
			k++;
		if (str[i][k] == 'r')
			new[++j] = '1';
		else if (str[i][k] == '%')
		{
			new[j] = '1';
			j++;
		}
		else
		{
			new[j] = '1';
			new[++j] = '1';
		}
		j++;
	}
	return (new);
}

int				ft_encoding(t_ligne **line)
{
	char		**str;
	int			k;
	char		*new;
	int			i;
	int			j;

	k = 0;
	j = 128;
	i = 0;
	if ((str = ft_strsplit((*line)->arg, ',')) == NULL)
		return (0);
	if ((new = ft_encoding_suite(str, i, -1)) == NULL)
		return (0);
	while (new[k])
	{
		i = (new[k] == '1') ? i + j : i;
		j = j / 2;
		k++;
	}
	ft_strdel_tab(&str);
	ft_strdel(&new);
	return (i);
}
