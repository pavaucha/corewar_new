/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:00 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:01 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_d_plus_space_preci(t_flags flags, char **s, int len, int *i)
{
	if (flags.plus == 1)
	{
		if (flags.sign == -1)
			(*s)[*i] = '-';
		else
			(*s)[*i] = '+';
	}
	else if (flags.space == 1)
		(*s)[*i] = ' ';
	if (flags.space == 1 || flags.plus == 1)
		(*i)++;
	if ((flags.space == 1 || flags.plus == 1) && flags.preci > 0
			&& flags.zero == 1)
		len++;
	while (flags.preci > len)
	{
		(*s)[*i] = '0';
		flags.preci--;
		(*i)++;
	}
}

static void		ft_d_width(t_flags flags, char **s, int *len, int *i)
{
	if (flags.minus == 1)
	{
		if (flags.space == 1)
			len[0]--;
		while (*i < len[0])
		{
			(*s)[*i] = ' ';
			(*i)++;
		}
	}
	else if (flags.minus == 0)
	{
		if (flags.plus == 1 || flags.space == 1)
			flags.width--;
		while (flags.width > len[1] && flags.width > flags.preci)
		{
			(*s)[*i] = ' ';
			flags.width--;
			(*i)++;
		}
	}
}

static void		ft_d_val(uintmax_t val, char **s, int len, int *i)
{
	uintmax_t	temp;
	uintmax_t	power;

	if (len == 0)
		return ;
	if (val == 0)
	{
		(*s)[(*i)++] = '0';
		return ;
	}
	while (len > 0)
	{
		power = ft_power(10, len - 1);
		temp = val % power;
		(*s)[*i] = val / power + '0';
		val = temp;
		len--;
		(*i)++;
	}
}

void			ft_di2(t_flags flags, char **s, int *len, uintmax_t val)
{
	int		i;

	i = 0;
	if (flags.minus == 0)
		ft_d_width(flags, s, len, &i);
	ft_d_plus_space_preci(flags, s, len[1], &i);
	ft_d_val(val, s, len[1], &i);
	if (flags.minus == 1)
		ft_d_width(flags, s, len, &i);
}
