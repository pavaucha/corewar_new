/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:43 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:44 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		one_bit(wchar_t c)
{
	ft_putchar_fd(c, 2);
	return (1);
}

static int		two_bit(wchar_t c)
{
	wchar_t		one;
	wchar_t		two;

	one = 0xC0;
	two = 0x80;
	one += (c >> 6) & 0x1F;
	two += c & 0x3F;
	ft_putchar_fd(one, 2);
	ft_putchar_fd(two, 2);
	return (2);
}

static int		three_bit(wchar_t c)
{
	wchar_t		one;
	wchar_t		two;
	wchar_t		three;

	one = 0xE0;
	two = 0x80;
	three = 0x80;
	one += (c >> 12) & 0x0F;
	two += (c >> 6) & 0x3F;
	three += c & 0x3F;
	ft_putchar_fd(one, 2);
	ft_putchar_fd(two, 2);
	ft_putchar_fd(three, 2);
	return (3);
}

static int		four_bit(wchar_t c)
{
	wchar_t		one;
	wchar_t		two;
	wchar_t		three;
	wchar_t		four;

	one = 0xF0;
	two = 0x80;
	three = 0x80;
	four = 0x80;
	one += (c >> 18) & 0x07;
	two += (c >> 12) & 0x3F;
	three += (c >> 6) & 0x3F;
	four += c & 0x3F;
	ft_putchar_fd(one, 2);
	ft_putchar_fd(two, 2);
	ft_putchar_fd(three, 2);
	ft_putchar_fd(four, 2);
	return (4);
}

int				ft_wchar(wchar_t c)
{
	if (c <= 0x7F)
		return (one_bit(c));
	else if (c <= 0x7FF)
		return (two_bit(c));
	else if (c <= 0xFFFF)
		return (three_bit(c));
	else if (c <= 0x1FFFFF)
		return (four_bit(c));
	else
		return (-1);
}
