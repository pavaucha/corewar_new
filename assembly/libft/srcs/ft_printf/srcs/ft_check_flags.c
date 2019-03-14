/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:05:49 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:05:50 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		digit_val(const char **format, va_list ap)
{
	int		i;

	i = 0;
	if (**format == '.')
		(*format)++;
	if (**format == '*')
	{
		i = va_arg(ap, int);
		return (i);
	}
	if (ft_isdigit(**format) == 0)
		i = 0;
	while (ft_isdigit(**format) == 1)
	{
		i = ((**format) - '0') + (i * 10);
		(*format)++;
	}
	(*format)--;
	return (i);
}

static void		size_val(const char **format, t_flags *flags)
{
	if (**format == 'h' && flags->size < h)
	{
		flags->size = h;
		if (*(*format + 1) == 'h')
			flags->size = hh;
	}
	else if (**format == 'l' && flags->size < l)
	{
		flags->size = l;
		if (*(*format + 1) == 'l')
			flags->size = ll;
	}
	else if (**format == 'j' && flags->size < j)
		flags->size = j;
	else if (**format == 'z' && flags->size < z)
		flags->size = z;
	if (flags->size == hh || flags->size == ll)
		(*format)++;
}

static void		flag(const char **format, t_flags *flags)
{
	if (**format == '#')
		flags->sharp = 1;
	else if (**format == '-')
		flags->minus = 1;
	else if (**format == '+')
		flags->plus = 1;
	else if (**format == '0')
		flags->zero = 1;
	else if (**format == ' ')
		flags->space = 1;
}

static void		reset_flags(t_flags *flags)
{
	flags->sharp = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->width = 0;
	flags->point = 0;
	flags->preci = 0;
	flags->sign = 1;
	flags->size = None;
}

t_arg			*ft_check_flags(const char **format, va_list ap, t_arg *arg)
{
	reset_flags(&(arg->flags));
	if (**format == '\0')
		return (arg);
	while ((ft_strchr(SIZE, **format) || ft_strchr(FLAGS, **format)
				|| ft_isdigit(**format)) && **format != '\0')
	{
		if (ft_strchr(FLAGS, **format))
			flag(format, &(arg->flags));
		if ((ft_isdigit(**format) && **format != '0') || **format == '*')
		{
			arg->flags.width = digit_val(format, ap);
			if (arg->flags.width < 0)
				arg->flags.minus = 1;
			arg->flags.width *= (arg->flags.width < 0) ? -(1) : 1;
		}
		else if (**format == '.')
		{
			arg->flags.point = 1;
			arg->flags.preci = digit_val(format, ap);
		}
		if (ft_strchr(SIZE, **format))
			size_val(format, &(arg->flags));
		(*format)++;
	}
	return (arg);
}
