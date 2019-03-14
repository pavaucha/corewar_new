/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 17:29:20 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:48:51 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char c)
{
	char	*new_s;
	void	*s;
	size_t	len;

	s = (void*)s1;
	if (!s1 || !s2 || !c)
	{
		free(s);
		return (NULL);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	if (!(new_s = ft_strnew(len)))
		return (NULL);
	ft_strcpy(new_s, (char*)s1);
	ft_strcat(new_s, (char*)s2);
	new_s[len - 2] = c;
	free(s);
	return (new_s);
}
