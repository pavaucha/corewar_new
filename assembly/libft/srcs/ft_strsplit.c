/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:27 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:49:28 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_nb_mot(char const *s, char c)
{
	int		i;
	int		nb_mot;

	i = 0;
	nb_mot = 0;
	while (*(s + i) != '\0')
	{
		while (*(s + i) == c)
			i++;
		if (*(s + i) != '\0' && *(s + i) != c)
			nb_mot++;
		while (*(s + i) != '\0' && *(s + i) != c)
			i++;
		if (*(s + i) != '\0')
			i++;
	}
	return (nb_mot);
}

static char	**ft_newstr(char const *s, char c)
{
	int		i;
	int		j;
	int		size_mot;
	char	**str;

	i = 0;
	j = 0;
	if ((str = (char**)malloc(sizeof(char*) * (ft_nb_mot(s, c) + 1))) == NULL)
		return (NULL);
	while (j < ft_nb_mot(s, c))
	{
		while (*(s + i) == c)
			i++;
		size_mot = 0;
		while (*(s + i) != '\0' && *(s + i) != c)
		{
			i++;
			size_mot++;
		}
		if ((*(str + j) = (char*)malloc(sizeof(char) * (size_mot + 1))) == NULL)
			return (NULL);
		j++;
		i++;
	}
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (s == NULL || (str = ft_newstr(s, c)) == NULL)
		return (NULL);
	while (j < ft_nb_mot(s, c))
	{
		while (*(s + i) == c)
			i++;
		k = 0;
		while (*(s + i) != '\0' && *(s + i) != c)
		{
			*(*(str + j) + k++) = *(s + i);
			i++;
		}
		*(*(str + j++) + k) = '\0';
		i++;
	}
	*(str + j) = 0;
	return (str);
}
