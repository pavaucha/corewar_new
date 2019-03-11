/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:58 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:59 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_x_sharp_preci(t_flags flags, char **s, int len, int *i)
{
	if (flags.sharp == 1)
	{
		(*s)[(*i)++] = '0';
		(*s)[(*i)++] = 'X';
	}
	while (flags.preci > len)
	{
		(*s)[*i] = '0';
		flags.preci--;
		(*i)++;
	}
}

static void		ft_x_width(t_flags flags, char **s, int *len, int *i)
{
	if (flags.minus == 1)
	{
		while (*i < len[0])
		{
			(*s)[*i] = ' ';
			(*i)++;
		}
	}
	else if (flags.minus == 0)
	{
		if (flags.sharp == 1)
			flags.width -= 2;
		while (flags.width > len[1] && flags.width > flags.preci)
		{
			(*s)[*i] = ' ';
			flags.width--;
			(*i)++;
		}
	}
}

static void		ft_x_val(uintmax_t val, char **s, int *i, int len)
{
	int			j;
	char		*val_x;

	if (len == 0)
		return ;
	if (val == 0)
	{
		(*s)[(*i)++] = '0';
		return ;
	}
	val_x = ft_itoa_base(val, 16, 1);
	j = 0;
	while (val_x[j] != '\0')
	{
		(*s)[*i] = val_x[j];
		(*i)++;
		j++;
	}
	ft_strdel(&val_x);
}

void			ft_x2(t_flags flags, char **s, int *len, uintmax_t val)
{
	int			i;

	i = 0;
	if (flags.minus == 0)
		ft_x_width(flags, s, len, &i);
	ft_x_sharp_preci(flags, s, len[1], &i);
	ft_x_val(val, s, &i, len[1]);
	if (flags.minus == 1)
		ft_x_width(flags, s, len, &i);
}
