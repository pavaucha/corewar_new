/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:10 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:11 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_o_sharp_preci(t_flags flags, char **s, int len, int *i)
{
	if (flags.sharp == 1)
		(*s)[(*i)++] = '0';
	while (flags.preci > len)
	{
		(*s)[*i] = '0';
		flags.preci--;
		(*i)++;
	}
}

static void		ft_o_width(t_flags flags, char **s, int *len, int *i)
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
			flags.width--;
		while (flags.width > len[1] && flags.width > flags.preci)
		{
			if (flags.zero == 1)
				(*s)[*i] = '0';
			else if (flags.zero == 0)
				(*s)[*i] = ' ';
			flags.width--;
			(*i)++;
		}
	}
}

static void		ft_o_val(uintmax_t val, char **s, int *i, int len)
{
	int			j;
	char		*val_o;

	if (len == 0)
		return ;
	if (val == 0)
	{
		(*s)[(*i)++] = '0';
		return ;
	}
	val_o = ft_itoa_base(val, 8, 1);
	j = 0;
	while (val_o[j] != '\0')
	{
		(*s)[*i] = val_o[j];
		(*i)++;
		j++;
	}
	ft_strdel(&val_o);
}

void			ft_o2(t_flags flags, char **s, int *len, uintmax_t val)
{
	int			i;

	i = 0;
	if (flags.minus == 0)
		ft_o_width(flags, s, len, &i);
	ft_o_sharp_preci(flags, s, len[1], &i);
	ft_o_val(val, s, &i, len[1]);
	if (flags.minus == 1)
		ft_o_width(flags, s, len, &i);
}
