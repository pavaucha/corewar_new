/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:14:16 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/12 11:12:33 by pavaucha         ###   ########.fr       */
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

static intmax_t	ft_overflow(char *str, int *sign)
{
	intmax_t	nb;
	int			i;

	nb = 0;
	i = (str[0] == '-') ? 1 : 0;
	(*sign) = (str[0] == '-') ? 0 : 1;
	if (ft_strlen(str + i) > 19)
		nb = ((*sign) == 1) ? 1 : 0;
	if (ft_strlen(str + i) == 19)
	{
		if (str[i] != '9')
			return (ft_atoi(str + i));
		nb = ft_atoi(str + 1 + i);
		if (nb <= 223372036854775808 && str[i] == '9' && i == 1)
		{
			(*sign) = i;
			return (nb = ft_atoi(str + 1));
		}
		else if (nb <= 223372036854775807 && str[i] == '9' && i == 0)
		{
			(*sign) = i;
			return (nb = ft_atoi(str + 1));
		}
		else
			nb = ((*sign) == 1) ? 1 : 0; 
	}
	return (nb);
}

static void	ft_complete_write(t_ligne **line, char *str, int l, int fd)
{
	int			sign;
	intmax_t	nb;
	int			i;

	i = (str[0] == '%') ? 1 : 0;
	sign = 0;
	if (str[i] == ':' || str[i] == ':')
	{
		nb = (*line)->pos[l];
		nb = ((*line)->pos[l] < 0) ? -nb : nb;
		if ((*line)->pos[l] < 0)
			sign = 1;
	}
	else
	{
		nb = ft_atoi(str + i);
		nb = (nb < 0) ? -nb : nb;
		if (ft_atoi(str + i) < 0)
			sign = 1;
		if (ft_strlen(str + i + sign) >= 19)
			nb = ft_overflow(str + i, &sign);
	}
	if (instruct_space(line) == 1 || str[0] == ':')
		ft_affiche(nb, sign, 16, fd);
	else if (instruct_space(line) == 0 && str[0] == '%')
		ft_affiche(nb, sign, 32, fd);
	else
		ft_affiche(nb, sign, 16, fd);
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
			ft_complete_write(line, str[k] + j, l, fd);
		else if (str[k][j] == ':')
			ft_complete_write(line, str[k] + j, l, fd);
		else
			ft_complete_write(line, str[k] + j, l, fd);
		l = (str[k][j + 1] == ':' || str[k][j] == ':') ? l + 1 : l;
	}
	ft_strdel_tab(&str);
}
