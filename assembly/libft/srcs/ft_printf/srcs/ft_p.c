/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:17 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:19 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_p_len(t_flags *flags, int len)
{
	if (flags->minus == 1 || (flags->point == 1 && flags->preci > -1))
		flags->zero = 0;
	if (flags->preci < len - 2)
		flags->preci = 0;
	else
		len = flags->preci + 2;
	if (flags->width < len)
		flags->width = 0;
	else
		len = flags->width;
	if (flags->width > 0 && flags->zero == 1)
	{
		flags->preci = flags->width - 2;
		flags->width = 0;
	}
	return (len);
}

int				ft_p(va_list ap, t_flags flags)
{
	uintmax_t	val;
	int			len[2];
	char		*s;
	int			i;

	val = (uintmax_t)va_arg(ap, uintptr_t);
	len[1] = ft_num_len(val, 16);
	len[1] += 2;
	if (val == 0 && flags.preci == 0 && flags.point == 1)
		len[1] = 2;
	len[0] = ft_p_len(&flags, len[1]);
	if ((s = (char*)malloc(sizeof(char) * (len[0] + 1))) == NULL)
		return (-1);
	s[len[0]] = '\0';
	ft_p2(flags, &s, len, val);
	i = -1;
	while (s[++i] != '\0')
		if (ft_isalpha(s[i]) == 1)
			s[i] = ft_tolower(s[i]);
	ft_putstr_fd(s, 2);
	ft_strdel(&s);
	return (len[0]);
}
