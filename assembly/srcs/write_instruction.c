/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 20:14:16 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/13 16:17:37 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

static int		instruct_space(t_ligne **line)
{
	if (ft_strcmp((*line)->instruct, "lldi") == 0
			|| ft_strcmp((*line)->instruct, "sti") == 0
			|| ft_strcmp((*line)->instruct, "ldi") == 0
			|| ft_strcmp((*line)->instruct, "zjmp") == 0
			|| ft_strcmp((*line)->instruct, "lfork") == 0
			|| ft_strcmp((*line)->instruct, "fork") == 0)
		return (1);
	else
		return (0);
}

static void		ft_affiche(intmax_t nb, int sign, int size, int fd)
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

static void		ft_complete_write(t_ligne **line, char *str, int l, int fd)
{
	int			sign;
	intmax_t	nb;
	int			i;

	i = (str[0] == '%') ? 1 : 0;
	if (str[i] == ':')
	{
		nb = (*line)->pos[l];
		nb = ((*line)->pos[l] < 0) ? -nb : nb;
		sign = ((*line)->pos[l] < 0) ? 1 : 0;
	}
	else
	{
		nb = ft_atoi(str + i);
		nb = (nb < 0) ? -nb : nb;
		sign = (ft_atoi(str + i) < 0) ? 1 : 0;
		if (ft_strlen(str + i) >= 19)
			nb = ft_overflow(str + i, &sign);
	}
	if (instruct_space(line) == 1 || str[0] == ':')
		ft_affiche(nb, sign, 16, fd);
	else if (instruct_space(line) == 0 && str[0] == '%')
		ft_affiche(nb, sign, 32, fd);
	else
		ft_affiche(nb, sign, 16, fd);
}

static char		**trim_instruct(t_ligne **line)
{
	int			i;
	char		*tmp;
	char		**str;

	i = -1;
	if ((str = ft_strsplit((*line)->arg, ',')) == NULL)
		return (NULL);
	while (str[++i])
	{
		tmp = str[i];
		if ((str[i] = ft_strtrim(str[i])) == NULL)
			return (NULL);
		ft_strdel(&tmp);
	}
	return (str);
}

void			ft_write_arg(t_ligne **line, int k, int fd)
{
	char		**str;
	int			j;
	int			l;
	intmax_t	nb;

	l = 0;
	if ((str = trim_instruct(line)) == NULL)
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
