/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 21:54:14 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 14:27:57 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				ft_islabel(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != ',')
		i++;
	return (i);
}

int				ft_find_label_instruct(int *k, t_ligne **nline, char **str)
{
	int			i;
	int			j;

	j = -1;
	i = 0;
	ft_memset((*nline)->pos, 0, 3);
	while (str[++(*k)] && (*nline)->instruct[0] == '\0')
	{
		if (str[*k] && ft_isalpha(str[*k][i]))
		{
			while (str[*k][i] && str[*k][i] != ':')
				i++;
			i = (str[*k][i] == '\0') ? 0 : i + 1;
			while (str[*k][i] && ft_isblank(str[*k][i]))
				i++;
			if (str[*k][i] != '\0')
				while (j < 6)
					(*nline)->instruct[++j] = (str[*k][i]
						&& ft_isalpha(str[*k][i])) ? str[*k][i++] : '\0';
			else
				i = 0;
		}
	}
	(*k)--;
	return (i);
}

char			*ft_strnew_c(size_t size, char c)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((str = (char*)ft_memalloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i < size)
	{
		*(str + i) = c;
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
