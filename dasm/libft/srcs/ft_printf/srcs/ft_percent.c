/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:06:25 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 16:06:26 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int		ft_percent_len(t_flags *flags)
{
	if (flags->minus == 1)
		flags->zero = 0;
	if (flags->width > 0)
		return (flags->width);
	return (1);
}

static void		ft_percent_minus(char **s, t_flags flags, int i, int len)
{
	if (flags.zero == 1)
	{
		while (++i < len - 1)
			(*s)[i] = '0';
	}
	else if (flags.zero == 0)
	{
		while (++i < len - 1)
			(*s)[i] = ' ';
	}
	(*s)[i] = '%';
}

int				ft_percent(t_flags flags)
{
	char	*s;
	int		i;
	int		len;

	len = ft_percent_len(&flags);
	if ((s = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (-1);
	s[len] = '\0';
	i = -1;
	if (flags.minus == 1)
	{
		s[++i] = '%';
		while (++i < len)
			s[i] = ' ';
	}
	else if (flags.minus == 0)
		ft_percent_minus(&s, flags, i, len);
	ft_putstr_fd(s, 2);
	ft_strdel(&s);
	return (len);
}
