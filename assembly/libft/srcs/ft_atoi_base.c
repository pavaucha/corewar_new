/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:44:44 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:47:41 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_base_a_f(const char *str, int base, int i)
{
	int		result;

	result = 0;
	while ((*(str + i) >= '0' && *(str + i) <= '9') || (*(str + i) >= 'A'
			&& *(str + i) <= 'F') || (*(str + i) >= 'a' && *(str + i) <= 'f'))
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
			result = ((*(str + i) - '0') + (result * base));
		else if (*(str + i) >= 'A' && *(str + i) <= 'F')
			result = ((*(str + i) - 'A' + 10) + (result * base));
		else if (*(str + i) >= 'a' && *(str + i) <= 'f')
			result = ((*(str + i) - 'a' + 10) + (result * base));
		i++;
	}
	return (result);
}

static int	ft_base_two_ten(const char *str, int base, int i)
{
	int		result;

	result = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		result = ((*(str + i) - '0') + (result * base));
		i++;
	}
	return (result);
}

int			ft_atoi_base(const char *str, int base)
{
	int		result;
	int		sign;
	int		i;

	if (str == NULL)
		return (-1);
	i = 0;
	sign = 1;
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
	result = (base < 11) ? ft_base_two_ten(str, base, i) :
		ft_base_a_f(str, base, i);
	return (result * sign);
}
