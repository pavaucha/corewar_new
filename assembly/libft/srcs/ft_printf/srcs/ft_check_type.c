/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:05:53 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:05:55 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	ft_spe(const char **format, va_list ap, t_arg *arg)
{
	int		len;

	len = 0;
	if (**format == 'd' || **format == 'i' || **format == 'D')
		len = ft_di(format, ap, arg->flags);
	else if (**format == 'u' || **format == 'U')
		len = ft_u(format, ap, arg->flags);
	else if (**format == 'o' || **format == 'O')
		len = ft_o(format, ap, arg->flags);
	else if (**format == 'x' || **format == 'X')
		len = ft_x(format, ap, arg->flags);
	else if (**format == 'c' || **format == 'C')
		len = ft_c(format, ap, arg->flags);
	else if (**format == 's' || **format == 'S')
		len = ft_s(format, ap, arg->flags);
	else if (**format == 'p')
		len = ft_p(ap, arg->flags);
	else if (**format == '%')
		len = ft_percent(arg->flags);
	return (len);
}

t_arg		*ft_check_type(const char **format, va_list ap, t_arg *arg)
{
	int		len;

	len = 0;
	if (**format == '\0')
		return (arg);
	if (ft_strchr(SPE, **format))
		len = ft_spe(format, ap, arg);
	else if (ft_isprint(**format))
		len = ft_other(format, arg->flags);
	if (len == -1)
	{
		arg->len = -1;
		return (arg);
	}
	arg->len += len;
	(*format)++;
	return (arg);
}
