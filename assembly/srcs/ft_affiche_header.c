/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affiche_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:00:52 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/12 18:29:28 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_put_swap(char *str)
{
	int		i;
	int		j;
	char	*dst;

	j = -1;
	if ((dst = ft_strnew(32)) == NULL)
		return (NULL);
	i = 23;
	while (++i < 32)
		dst[++j] = str[i];
	i = 15;
	while (++i < 24)
		dst[++j] = str[i];
	i = 7;
	while (++i < 16)
		dst[++j] = str[i];
	i = -1;
	while (++i < 8)
		dst[++j] = str[i];
	ft_strdel(&str);
	return (dst);
}

int			ft_swap_bits(char *dst, int sign)
{
	int			i;
	int			j;
	char		*str;

	j = -1;
	if ((str = ft_strnew(32)) == NULL)
		return (-1);
	i = (int)ft_strlen(dst) - 1;
	while (++i < 32)
		str[++j] = '0';
	i = (ft_strlen(dst) > 32) ? (int)(ft_strlen(dst) - 32) - 1 : -1;
	while (j < 32)
		str[++j] = dst[++i];
	ft_strdel(&dst);
	if (sign == 1)
	{
		dst = ft_negative_nb(str, 32);
		dst = ft_put_swap(dst);
	}
	else
		dst = ft_put_swap(str);
	i = ft_atoi_base(dst, 2);
	ft_strdel(&dst);
	return (i);
}

void		ft_affiche_header(t_header head, int fd, t_ligne *line, char c)
{
	int		i;

	i = ft_swap_bits(ft_itoa_base(COREWAR_EXEC_MAGIC, 2, 1), 0);
	(i != -1) ? write(fd, &i, sizeof(int)) : 0;
	i = -1;
	while (++i < 132)
	{
		if (i < (int)ft_strlen(head.prog_name))
			head.prog_name[i] == 127 ? write(fd, "\n", 1)
				: write(fd, &head.prog_name[i], 1);
		else
			write(fd, &c, 1);
	}
	i = ft_swap_bits(ft_itoa_base((uintmax_t)line->nb_octet_pos, 2, 1), 0);
	(i != -1) ? write(fd, &i, sizeof(int)) : 0;
	i = -1;
	while (++i < 2052)
	{
		if (i < (int)ft_strlen(head.comment))
			head.comment[i] == 127 ? write(fd, "\n", 1)
				: write(fd, &head.comment[i], 1);
		else
			write(fd, &c, 1);
	}
}
