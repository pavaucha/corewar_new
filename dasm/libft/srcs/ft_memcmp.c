/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:57:54 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 15:53:18 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*tab1;
	unsigned const char	*tab2;
	size_t				i;

	tab1 = s1;
	tab2 = s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (i < (n - 1) && (tab1[i] == tab2[i]))
		i++;
	return ((int)(tab1[i] - tab2[i]));
}
