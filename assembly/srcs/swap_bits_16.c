/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits_16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:24:54 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/12 17:57:53 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*ft_negative_nb(char *str, int i)
{
	int		j;
	char	*dst;

	j = -1;
	if ((dst = ft_strnew(i)) == NULL)
		return (NULL);
	while (str[++j])
		dst[j] = (str[j] == '0') ? '1' : '0';
	while (--j > 0 && dst[j] != '0')
		dst[j] = '0';
	dst[j] = (dst[j] == '1') ? '0' : '1';
	ft_strdel(&str);
	return (dst);
}

static char	*ft_put_swap_16(char *str)
{
	int		i;
	int		j;
	char	*dst;

	j = -1;
	if ((dst = ft_strnew(16)) == NULL)
		return (NULL);
	i = 7;
	while (++i < 16)
		dst[++j] = str[i];
	i = -1;
	while (++i < 8)
		dst[++j] = str[i];
	ft_strdel(&str);
	return (dst);
}

int			ft_swap_bits_16(char *dst, int sign)
{
	int			i;
	int			j;
	char		*str;

	j = -1;
	if ((str = ft_strnew(16)) == NULL)
		return (-1);
	i = (int)ft_strlen(dst) - 1;
	while (++i < 16)
		str[++j] = '0';
	i = (ft_strlen(dst) > 16) ? (int)(ft_strlen(dst) - 16) - 1 : -1;
	while (j < 16)
		str[++j] = dst[++i];
	ft_strdel(&dst);
	if (sign == 1)
	{
		dst = ft_negative_nb(str, 16);
		dst = ft_put_swap_16(dst);
	}
	else
		dst = ft_put_swap_16(str);
	i = ft_atoi_base(dst, 2);
	ft_strdel(&dst);
	return (i);
}
