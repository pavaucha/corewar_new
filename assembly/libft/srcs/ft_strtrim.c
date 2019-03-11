/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:33 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:49:34 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	int		go;
	int		end;
	char	*str;

	end = 0;
	go = 0;
	if (s == NULL)
		return (NULL);
	while (*(s + end) != '\0')
		end++;
	end--;
	while (*(s + end) == ' ' || *(s + end) == '\t' || *(s + end) == '\n')
		end--;
	while (*(s + go) == ' ' || *(s + go) == '\t' || *(s + go) == '\n')
		go++;
	if (go > end)
		return (ft_strnew(0));
	if ((str = ft_strsub(s, go, (end - go + 1))) == NULL)
		return (NULL);
	return (str);
}
