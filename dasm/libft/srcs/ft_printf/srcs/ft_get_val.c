/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:03 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:05 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

intmax_t	ft_get_int_val(va_list ap, t_flags flags)
{
	intmax_t	val;

	val = 0;
	if (flags.size == None)
		val = (intmax_t)va_arg(ap, int);
	else if (flags.size == l)
		val = (intmax_t)va_arg(ap, long int);
	else if (flags.size == ll)
		val = (intmax_t)va_arg(ap, long long int);
	else if (flags.size == h)
		val = (intmax_t)((short)va_arg(ap, int));
	else if (flags.size == hh)
		val = (intmax_t)((char)va_arg(ap, int));
	else if (flags.size == j)
		val = va_arg(ap, intmax_t);
	else if (flags.size == z)
		val = (intmax_t)va_arg(ap, size_t);
	return (val);
}

uintmax_t	ft_get_uint_val(va_list ap, t_flags flags)
{
	uintmax_t	val;

	val = 0;
	if (flags.size == None)
		val = (uintmax_t)va_arg(ap, unsigned int);
	else if (flags.size == l)
		val = (uintmax_t)va_arg(ap, long unsigned int);
	else if (flags.size == ll)
		val = (uintmax_t)va_arg(ap, unsigned long long int);
	else if (flags.size == h)
		val = (uintmax_t)((unsigned short)va_arg(ap, int));
	else if (flags.size == hh)
		val = (uintmax_t)((unsigned char)va_arg(ap, int));
	else if (flags.size == j)
		val = va_arg(ap, uintmax_t);
	else if (flags.size == z)
		val = (uintmax_t)va_arg(ap, size_t);
	return (val);
}
