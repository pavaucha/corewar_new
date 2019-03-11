/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:13 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:14 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		ft_other_flags(t_flags *flags)
{
	if (flags->minus == 1)
		flags->zero = 0;
}

static void		ft_other_width(t_flags flags, int *len)
{
	if (flags.minus == 1)
	{
		while (flags.width > 1)
		{
			ft_putchar_fd(' ', 2);
			(*len)++;
			flags.width--;
		}
	}
	else if (flags.minus == 0)
	{
		while (flags.width > 1)
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

int				ft_other(const char **format, t_flags flags)
{
	int			len;

	len = 0;
	ft_other_flags(&flags);
	if (flags.minus == 0)
		ft_other_width(flags, &len);
	ft_putchar_fd(**format, 2);
	len++;
	if (flags.minus == 1)
		ft_other_width(flags, &len);
	return (len);
}
