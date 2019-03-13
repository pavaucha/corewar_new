/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 06:56:35 by mavui             #+#    #+#             */
/*   Updated: 2019/02/11 06:56:39 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		lex_err(char *buf, int i)
{
	if (ft_isalnum(buf[i]) && !(buf[i] >= 'A' && buf[i] <= 'Z'))
		return (0);
	if (buf[i] == '\t' || buf[i] == ' ' || buf[i] == '"' || buf[i] == '#'
		|| buf[i] == ',' || buf[i] == ';' || buf[i] == '_')
		return (0);
	if (i > 0 && buf[i] == ':' && !(buf[i - 1] >= 'A' && buf[i - 1] <= 'Z')
		&& (ft_isalnum(buf[i - 1]) || buf[i - 1] == '_'))
		return (0);
	if (buf[i] == ':' && (ft_isalpha(buf[i + 1]) || ft_isdigit(buf[i + 1]) || buf[i + 1] == '_'))
		return (0);
	if (buf[i] == '-' && ft_isdigit(buf[i + 1]))
		return (0);
	if (buf[i] == '%' && (ft_isdigit(buf[i + 1])))
		return (0);
	if (buf[i] == '%' && (buf[i + 1] == ':' || buf[i + 1] == '-')
		&& (ft_isalnum(buf[i + 2]) || buf[i + 2] == '_'))
		return (buf[i + 2] >= 'A' && buf[i + 2] <= 'Z' ? 1 : 0);
	return (1);
}

int		double_header(t_file *x, char *buf, int i)
{
	if (!ft_strncmp(buf + i, ".name", 5))
	{
		x->c += i;
		save_err(x, x->c, 2);
		return (1);
	}
	else if (!ft_strncmp(buf + i, ".comment", 8))
	{
		x->c += i;
		save_err(x, x->c, 4);
		return (1);
	}
	return (0);
}

void	check_quote(t_file *x, int *save, int *quote, int i)
{
	(*quote)++;
	if (i == 0 && x->err != 17 && x->err != 18)
	{
		(*save) = x->err;
		x->err = 18;
	}
	else if (x->err == 18 && !x->body)
	{
		x->err = (*save) ? (*save) : 19;
		if (!x->body)
			x->err = 0;
	}
}

int		char_err(char *buf, t_file *x)
{
	static int	save = 0;
	int			quote;
	int			i;

	i = 0;
	quote = 0;
	while (buf[i])
	{
		if ((buf[i] == '#' || buf[i] == ';') && x->err != 18)
			break ;
		else if (buf[i] == '"')
			check_quote(x, &save, &quote, i);
		else if (quote % 2 == 1 && x->err == 18)
			;
		else if (double_header(x, buf, i) == 1)
			;
		else if (lex_err(buf, i))
		{
			x->c = i;
			return (save_err(x, x->c, 5));
		}
		i++;
	}
	return (0);
}
