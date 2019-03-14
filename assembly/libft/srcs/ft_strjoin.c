/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:48:48 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:48:49 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*str;

	len_s1 = 0;
	len_s2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (*(s1 + len_s1) != '\0')
		len_s1++;
	while (*(s2 + len_s2) != '\0')
		len_s2++;
	if (!(str = (char*)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	if (str == NULL)
		return (NULL);
	*(str + len_s1 + len_s2) = '\0';
	while (len_s2-- > 0 && *(s2 + len_s2) != '\0')
		*(str + len_s1 + len_s2) = *(s2 + len_s2);
	while (len_s1-- > 0 && *(s1 + len_s1) != '\0')
		*(str + len_s1) = *(s1 + len_s1);
	return (str);
}
