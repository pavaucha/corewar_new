/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:18:33 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/13 16:18:35 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static intmax_t	ft_complete_overflow(intmax_t nb, char *str, int i, int *sign)
{
	if (nb <= 223372036854775808 && str[i] == '9' && i == 1)
	{
		nb = ft_atoi(str);
		nb = (nb < 0) ? -nb : nb;
		(*sign) = (ft_atoi(str) < 0) ? 1 : 0;
		return (nb);
	}
	else if (nb <= 223372036854775807 && str[i] == '9' && i == 0)
	{
		nb = ft_atoi(str);
		(*sign) = 0;
		return (nb);
	}
	nb = (i == 1) ? 0 : 1;
	(*sign) = (i == 1) ? 0 : 1;
	return (nb);
}

intmax_t		ft_overflow(char *str, int *sign)
{
	intmax_t	nb;
	int			i;

	nb = 0;
	i = (str[0] == '-') ? 1 : 0;
	if (ft_strlen(str + i) > 19)
	{
		(*sign) = (i == 1) ? 0 : 1;
		nb = (i == 1) ? 0 : 1;
	}
	if (ft_strlen(str + i) == 19)
	{
		if (str[i] != '9')
			return (ft_atoi(str + i));
		nb = ft_complete_overflow(ft_atoi(str + i + 1), str, i, sign);
	}
	return (nb);
}
