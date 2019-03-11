/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:20:43 by pavaucha          #+#    #+#             */
/*   Updated: 2018/11/03 14:07:25 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"
# include <wchar.h>
# define FLAGS "#-+0 .*"
# define SPE "sSpdDioOuUxXcC%"
# define SIZE "hljz"

typedef enum	e_size
{
	None = 0,
	h,
	hh,
	z,
	l,
	ll,
	j
}				t_size;

typedef struct	s_flags
{
	int			sharp;
	int			minus;
	int			plus;
	int			zero;
	int			space;
	int			width;
	int			point;
	int			preci;
	int			sign;
	t_size		size;
}				t_flags;

typedef struct	s_arg
{
	t_flags		flags;
	int			len;
}				t_arg;

int				ft_printf(const char *formatc, ...);
t_arg			*ft_check_flags(const char **format, va_list ap, t_arg *arg);
t_arg			*ft_check_type(const char **format, va_list ap, t_arg *arg);
intmax_t		ft_get_int_val(va_list ap, t_flags flags);
uintmax_t		ft_get_uint_val(va_list ap, t_flags flags);
int				ft_wchar(wchar_t c);
int				ft_wchar_len(wchar_t c);
int				ft_wstr(wchar_t *wch, int width);
int				ft_wstr_len(wchar_t *wch, int width);
int				ft_percent(t_flags flags);
int				ft_other(const char **format, t_flags flags);
int				ft_di(const char **format, va_list ap, t_flags flags);
void			ft_di2(t_flags flags, char **s, int *len, uintmax_t val);
int				ft_u(const char **format, va_list ap, t_flags flags);
int				ft_o(const char **format, va_list ap, t_flags flags);
void			ft_o2(t_flags flags, char **s, int *len, uintmax_t val);
int				ft_x(const char **format, va_list ap, t_flags flags);
void			ft_x2(t_flags flags, char **s, int *len, uintmax_t val);
int				ft_p(va_list ap, t_flags flags);
void			ft_p2(t_flags flags, char **s, int *len, uintmax_t val);
int				ft_c(const char **format, va_list ap, t_flags flags);
int				ft_s(const char **format, va_list ap, t_flags flags);
int				ft_bigs(va_list ap, t_flags flags);

#endif
