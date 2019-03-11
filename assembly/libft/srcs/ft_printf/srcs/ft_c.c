/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:05:44 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:05:47 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_c_flags(t_flags *flags)
{
	if (flags->minus == 1)
		flags->zero = 0;
}

static void		ft_c_width(t_flags flags, int *len)
{
	int		i;

	i = *len;
	if (flags.minus == 1)
	{
		while (flags.width > i)
		{
			ft_putchar_fd(' ', 2);
			(*len)++;
			flags.width--;
		}
	}
	else if (flags.minus == 0)
	{
		while (flags.width > i)
		{
			if (flags.zero == 0)
				ft_putchar_fd(' ', 2);
			else if (flags.zero == 1)
				ft_putchar_fd('0', 2);
			(*len)++;
			flags.width--;
		}
	}
}

static int		ft_wch(va_list ap, t_flags flags)
{
	wchar_t		wch;
	int			len;

	len = 0;
	wch = (wchar_t)va_arg(ap, wint_t);
	if ((len = ft_wchar_len(wch)) == -1)
		return (-1);
	if (flags.minus == 0)
		ft_c_width(flags, &len);
	if ((ft_wchar(wch)) == -1)
		return (-1);
	if (flags.minus == 1)
		ft_c_width(flags, &len);
	return (len);
}

int				ft_c(const char **format, va_list ap, t_flags flags)
{
	char		ch;
	int			len;

	if (flags.size == l || **format == 'C')
		return (ft_wch(ap, flags));
	ft_c_flags(&flags);
	ch = (char)va_arg(ap, int);
	len = 1;
	if (flags.minus == 0)
		ft_c_width(flags, &len);
	ft_putchar_fd(ch, 2);
	if (flags.minus == 1)
		ft_c_width(flags, &len);
	return (len);
}
