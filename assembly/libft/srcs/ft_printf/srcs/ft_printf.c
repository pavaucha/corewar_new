/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:28 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:29 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	ft_flags_type(const char **format, va_list ap, t_arg *arg)
{
	(*format)++;
	if (**format == '\0')
		return ;
	ft_check_flags(format, ap, arg);
	if (**format == '\0')
		return ;
	ft_check_type(format, ap, arg);
	if (arg->len == -1)
		return ;
}

static int	ft_start(const char *format, va_list ap)
{
	t_arg		arg;
	int			len;
	int			j;

	len = 0;
	arg.len = 0;
	while (*format != '\0')
	{
		j = 0;
		while (*(format + j) != '%' && *(format + j) != '\0')
			j++;
		ft_putnstr(format, j);
		format += j;
		len += j;
		if (*format == '%')
			ft_flags_type(&format, ap, &arg);
	}
	len += arg.len;
	if (arg.len == -1)
		len = -1;
	return (len);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, format);
	len = ft_start(format, ap);
	va_end(ap);
	return (len);
}
