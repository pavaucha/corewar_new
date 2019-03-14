/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:21 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:22 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_p_0x_preci(char **s, int *i, t_flags flags, int len)
{
	(*s)[(*i)++] = '0';
	(*s)[(*i)++] = 'x';
	while (flags.preci > len - 2)
	{
		(*s)[*i] = '0';
		flags.preci--;
		(*i)++;
	}
}

static void		ft_p_width(t_flags flags, char **s, int *len, int *i)
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
		while (flags.width > len[1])
		{
			(*s)[*i] = ' ';
			(*i)++;
			flags.width--;
		}
	}
}

static void		ft_p_val(uintmax_t val, char **s, int *i, int len)
{
	int			j;
	char		*val_p;

	if (len == 2)
		return ;
	if (val == 0)
	{
		(*s)[(*i)++] = '0';
		return ;
	}
	val_p = ft_itoa_base(val, 16, 1);
	j = 0;
	while (val_p[j] != '\0')
	{
		(*s)[*i] = val_p[j];
		(*i)++;
		j++;
	}
	ft_strdel(&val_p);
}

void			ft_p2(t_flags flags, char **s, int *len, uintmax_t val)
{
	int		i;

	i = 0;
	if (flags.minus == 0)
		ft_p_width(flags, s, len, &i);
	ft_p_0x_preci(s, &i, flags, len[1]);
	ft_p_val(val, s, &i, len[1]);
	if (flags.minus == 1)
		ft_p_width(flags, s, len, &i);
}
