/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:40 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:42 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_u_len(t_flags *flags, int len)
{
	if (flags->minus == 1 || (flags->point == 1 && flags->preci > -1))
		flags->zero = 0;
	if (flags->preci < len)
		flags->preci = 0;
	else
		len = flags->preci;
	if (flags->width < len)
		flags->width = 0;
	else
		len = flags->width;
	return (len);
}

static void		ft_u_preci(t_flags flags, char **s, int len, int *i)
{
	while (flags.preci > len)
	{
		(*s)[*i] = '0';
		flags.preci--;
		(*i)++;
	}
}

static void		ft_u_width(t_flags flags, char **s, int *len, int *i)
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

static void		ft_u_val(uintmax_t val, char **s, int len, int *i)
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

int				ft_u(const char **format, va_list ap, t_flags flags)
{
	uintmax_t	val;
	int			len[2];
	char		*s;
	int			i;

	if (**format == 'U')
		flags.size = l;
	val = ft_get_uint_val(ap, flags);
	len[1] = ft_num_len(val, 10);
	if (val == 0 && flags.preci == 0 && flags.point == 1)
		len[1] = 0;
	len[0] = ft_u_len(&flags, len[1]);
	if ((s = (char*)malloc(sizeof(char) * (len[0] + 1))) == NULL)
		return (-1);
	s[len[0]] = '\0';
	i = 0;
	if (flags.minus == 0)
		ft_u_width(flags, &s, len, &i);
	ft_u_preci(flags, &s, len[1], &i);
	ft_u_val(val, &s, len[1], &i);
	if (flags.minus == 1)
		ft_u_width(flags, &s, len, &i);
	ft_putstr_fd(s, 2);
	ft_strdel(&s);
	return (len[0]);
}
