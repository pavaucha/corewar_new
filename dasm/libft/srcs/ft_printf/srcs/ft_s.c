/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:36 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:38 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_s_len(t_flags *flags, int len)
{
	if (flags->preci < 0)
		flags->point = 0;
	if (flags->point == 1 && flags->preci == 0)
		return (0);
	if (flags->minus == 1)
		flags->zero = 0;
	if (len < flags->preci)
	{
		flags->preci = 0;
		flags->point = 0;
	}
	if (flags->preci > 0)
		len = flags->preci;
	if (flags->width < len)
		flags->width = 0;
	else
		len = flags->width;
	return (len);
}

static int		ft_s_preci(t_flags flags)
{
	if (flags.preci == 0)
		return (0);
	else
		return (flags.preci);
}

static void		ft_s_width(t_flags flags, int len)
{
	if (flags.minus == 1)
	{
		while (flags.width-- > len)
			ft_putchar_fd(' ', 2);
	}
	else if (flags.minus == 0)
	{
		while (flags.width-- > len)
		{
			if (flags.zero == 0)
				ft_putchar_fd(' ', 2);
			else if (flags.zero == 1)
				ft_putchar_fd('0', 2);
		}
	}
}

int				ft_s(const char **format, va_list ap, t_flags flags)
{
	char		*s;
	int			len[2];

	len[1] = 0;
	if (flags.size == l || **format == 'S')
		return (ft_bigs(ap, flags));
	s = va_arg(ap, char *);
	if (s != NULL)
		len[1] = ft_strlen(s);
	else
	{
		len[1] = 6;
		s = "(null)";
	}
	len[0] = ft_s_len(&flags, len[1]);
	if (flags.point == 1)
		len[1] = ft_s_preci(flags);
	if (len[0] == 0 && flags.width != 0)
		len[0] = flags.width;
	if (flags.minus == 0)
		ft_s_width(flags, len[1]);
	ft_putnstr(s, len[1]);
	if (flags.minus == 1)
		ft_s_width(flags, len[1]);
	return (len[0]);
}
