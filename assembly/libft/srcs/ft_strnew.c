/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:14 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:49:16 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((str = (char*)ft_memalloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i < size)
	{
		*(str + i) = '\0';
		i++;
	}
	*(str + i) = '\0';
	return (str);
}
