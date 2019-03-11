/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:44:31 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:44:40 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

intmax_t	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	intmax_t		result;

	i = 0;
	sign = 1;
	result = 0;
	while (*(str + i) < 33 || *(str + i) > 126)
	{
		if (*(str + i) == '\0' || *(str + i) == '\200' || *(str + i) == 27)
			return (0);
		i++;
	}
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
			sign = -1;
		i++;
	}
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		result = ((*(str + i) - '0') + (result * 10));
		i++;
	}
	return (result * sign);
}
