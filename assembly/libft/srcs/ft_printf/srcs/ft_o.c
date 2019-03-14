/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:07 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:08 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_o_len(t_flags *flags, int len)
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
	if (flags->preci != 0 || (flags->width != 0 && flags->zero == 1))
		flags->sharp = 0;
	if (flags->sharp == 1 && flags->preci == 0 && flags->width == 0)
		len++;
	return (len);
}

int				ft_o(const char **format, va_list ap, t_flags flags)
{
	uintmax_t	val;
	int			len[2];
	char		*s;

	if (**format == 'O')
		flags.size = l;
	val = ft_get_uint_val(ap, flags);
	len[1] = ft_num_len(val, 8);
	if (val == 0 && ((flags.preci == 0 && flags.point == 1)
				|| flags.sharp == 1))
		len[1] = 0;
	len[0] = ft_o_len(&flags, len[1]);
	if ((s = (char*)malloc(sizeof(char) * (len[0] + 1))) == NULL)
		return (-1);
	s[len[0]] = '\0';
	ft_o2(flags, &s, len, val);
	ft_putstr_fd(s, 2);
	ft_strdel(&s);
	return (len[0]);
}
