/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:48:31 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:48:32 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	c = (char)c;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
		{
			found = 1;
			break ;
		}
		i++;
	}
	if (c == '\0')
		found = 1;
	if (found == 0)
		return (NULL);
	return ((char*)s + i);
}
