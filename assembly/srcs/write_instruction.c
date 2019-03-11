/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:14:16 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 16:05:08 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int	instruct_space(t_ligne **line)
{
	if (ft_strcmp((*line)->instruct, "lldi") == 0
			|| ft_strcmp((*line)->instruct, "sti") == 0
			|| ft_strcmp((*line)->instruct, "ldi") == 0
			|| ft_strcmp((*line)->instruct, "zjmp") == 0
			|| ft_strcmp((*line)->instruct, "fork") == 0)
		return (1);
	else
		return (0);
}

static void	ft_affiche(intmax_t nb, int sign, int size, int fd)
{
	if (size == 16)
	{
		nb = ft_swap_bits_16(ft_itoa_base((uintmax_t)nb, 2, 1), sign);
		write(fd, &nb, sizeof(int16_t));
	}
	else
	{
		nb = ft_swap_bits(ft_itoa_base((uintmax_t)nb, 2, 1), sign);
		write(fd, &nb, sizeof(int32_t));
	}
}

static void	ft_complete_write(t_ligne **line, char *str, int l, int fd)
{
	int			sign;
	intmax_t	nb;

	sign = 0;
	if (str[1] == ':' || str[0] == ':')
	{
		nb = (*line)->pos[l];
		nb = ((*line)->pos[l] < 0) ? -nb : nb;
		if ((*line)->pos[l] < 0)
			sign = 1;
	}
	else
	{
		ft_printf("%s\n", str + 1);
		nb = ft_atoi(str + 1);
		nb = (nb < 0) ? -nb : nb;
		if (ft_atoi(str + 1) < 0)
			sign = 1;
		ft_printf("nb = %lli\n", nb);
	}
	if (instruct_space(line) == 1 || str[0] == ':')
		ft_affiche(nb, sign, 16, fd);
	else
		ft_affiche(nb, sign, 32, fd);
}

void		ft_write_arg(t_ligne **line, int k, int fd)
{
	char		**str;
	int			j;
	int			l;
	intmax_t	nb;

	l = 0;
	if ((str = ft_strsplit((*line)->arg, ',')) == NULL)
		return ;
	while (str[++k])
	{
		j = 0;
		while (ft_isblank(str[k][j]))
			j++;
		nb = str[k][j] == 'r' ? ft_atoi(str[k] + j + 1) : ft_atoi(str[k] + j);
		if (str[k][j] == 'r')
			write(fd, &nb, 1);
		else if (ft_isdigit(str[k][j]) || str[k][j] == '-')
			ft_affiche(((nb < 0) ? -nb : nb), ((nb < 0) ? 1 : 0), 16, fd);
		else if (str[k][j] == ':')
			ft_complete_write(line, str[k] + j, l, fd);
		else
			ft_complete_write(line, str[k] + j, l, fd);
		l = (str[k][j + 1] == ':' || str[k][j] == ':') ? l + 1 : l;
	}
	ft_strdel_tab(&str);
}
