/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:23 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:49:24 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	c = (char)c;
	while (*(s + i) != '\0')
		i++;
	if (c == '\0')
		return ((char*)s + i);
	while (i > 0)
	{
		if (*(s + i - 1) == c)
		{
			found = 1;
			break ;
		}
		i--;
	}
	if (found == 0)
		return (NULL);
	return ((char*)s + i - 1);
}
