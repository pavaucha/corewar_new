/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:05:56 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:05:58 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	ft_d_len(t_flags *flags, int len)
{
	if (flags->sign == -1)
		flags->plus = 1;
	if (flags->minus == 1 || (flags->point == 1 && flags->preci > -1))
		flags->zero = 0;
	if (flags->preci < len)
		flags->preci = 0;
	else
		len = flags->preci;
	if (flags->plus == 1)
		len++;
	if (flags->width < len)
		flags->width = 0;
	else
		len = flags->width;
	if (flags->plus == 1 || (flags->minus == 1 && flags->width > len + 1)
			|| (flags->minus == 0 && flags->width > len))
		flags->space = 0;
	if (flags->space == 1 && (flags->minus == 1 || flags->width == 0))
		len++;
	if (flags->width > 0 && flags->zero == 1)
	{
		flags->preci = flags->width;
		flags->width = 0;
	}
	return (len);
}

int			ft_di(const char **format, va_list ap, t_flags flags)
{
	intmax_t	get;
	uintmax_t	val;
	int			len[2];
	char		*s;

	if (**format == 'D')
		flags.size = l;
	get = ft_get_int_val(ap, flags);
	if (get < 0)
		flags.sign = -1;
	val = get * flags.sign;
	len[1] = ft_num_len(val, 10);
	if (val == 0 && flags.preci == 0 && flags.point == 1)
		len[1] = 0;
	len[0] = ft_d_len(&flags, len[1]);
	if ((s = (char*)malloc(sizeof(char) * (len[0] + 1))) == NULL)
		return (-1);
	s[len[0]] = '\0';
	ft_di2(flags, &s, len, val);
	ft_putstr_fd(s, 2);
	ft_strdel(&s);
	return (len[0]);
}
