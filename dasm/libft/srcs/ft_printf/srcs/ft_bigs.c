/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bigs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:05:40 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:05:42 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_bigs_len(t_flags *flags, int len)
{
	if (flags->preci < 0)
		flags->point = 0;
	if (flags->point == 1 && flags->preci == 0)
		return (0);
	if (flags->minus == 1)
		flags->zero = 0;
	if (len < flags->preci)
	{
		flags->point = 0;
		flags->preci = 0;
	}
	if (flags->preci > 0)
		len = flags->preci;
	if (flags->width < len)
		flags->width = 0;
	else
		len = flags->width;
	return (len);
}

static int		ft_bigs_preci(wchar_t *ws, t_flags flags)
{
	int		i;

	i = 0;
	while (ws[i] != '\0' && flags.preci > 0)
	{
		if (ws[i] <= 0x7F)
			flags.preci--;
		else if (ws[i] <= 0x7FF && flags.preci >= 2)
			flags.preci -= 2;
		else if (ws[i] <= 0xFFFF && flags.preci >= 3)
			flags.preci -= 3;
		else if (ws[i] <= 0x1FFFFF && flags.preci >= 4)
			flags.preci -= 4;
		else
			return (i);
		i++;
	}
	return (i);
}

static void		ft_bigs_width(t_flags flags, int len)
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

static int		ft_bigs_put(t_flags flags, int *len, wchar_t *ws)
{
	int			temp;

	len[0] = ft_bigs_len(&flags, len[1]);
	if (flags.point == 1)
		len[1] = ft_bigs_preci(ws, flags);
	if (len[0] == 0 && flags.width != 0)
		len[0] = flags.width;
	if (flags.minus == 0)
		ft_bigs_width(flags, ft_wstr_len(ws, len[1]));
	if ((temp = ft_wstr(ws, len[1])) == -1)
		return (-1);
	if (temp + flags.width < len[0])
		len[0] = temp;
	if (flags.minus == 1)
		ft_bigs_width(flags, ft_wstr_len(ws, len[1]));
	return (len[0]);
}

int				ft_bigs(va_list ap, t_flags flags)
{
	wchar_t		*ws;
	int			len[2];
	int			i;

	len[1] = 0;
	ws = va_arg(ap, wchar_t *);
	i = 0;
	if (ws != NULL)
	{
		while (ws[i] != '\0')
			i++;
		if ((len[1] = ft_wstr_len(ws, i)) == -1)
			return (-1);
	}
	else
	{
		len[1] = 6;
		ws = L"(null)";
	}
	return (ft_bigs_put(flags, len, ws));
}
