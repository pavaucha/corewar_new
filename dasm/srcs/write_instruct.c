/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:39:11 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 10:39:04 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

static int		write_dir(int fd, t_champ champ, int i)
{
	char			*str;
	int				j;

	write(fd, "%", 1);
	champ = ft_is_negative(champ, i, 4, fd);
	if ((str = ft_strjoin_free(add_null(ft_itoa_base(champ.instructions[i], 2,
		1)), add_null(ft_itoa_base(champ.instructions[i + 1], 2, 1)))) == NULL)
		return (-1);
	if ((str = ft_strjoin_free(str,
		add_null(ft_itoa_base(champ.instructions[i + 2], 2, 1)))) == NULL)
		return (-1);
	if ((str = ft_strjoin_free(str,
		add_null(ft_itoa_base(champ.instructions[i + 3], 2, 1)))) == NULL)
		return (-1);
	j = ft_atoi_base(str, 2);
	ft_strdel(&str);
	str = ft_itoa(j);
	write(fd, str, ft_strlen(str));
	ft_strdel(&str);
	return (i + 4);
}

static int		write_reg(int fd, t_champ champ, int i)
{
	int				j;
	char			*str;

	if ((str = ft_itoa_base(champ.instructions[i], 2, 1)) == NULL)
		return (-1);
	j = ft_atoi_base(str, 2);
	ft_strdel(&str);
	if ((str = ft_itoa(j)) == NULL)
		return (-1);
	write(fd, "r", 1);
	write(fd, str, ft_strlen(str));
	ft_strdel(&str);
	return (i + 1);
}

static int		write_ind(int fd, t_champ champ, int i, int d)
{
	int				j;
	char			*str;

	if (d == 9 || d == 10 || d == 11 || d == 12 || d == 14 || d == 15)
		write(fd, "%", 1);
	champ = ft_is_negative(champ, i, 2, fd);
	if ((str = ft_strjoin_free(add_null(ft_itoa_base(champ.instructions[i], 2,
		1)), add_null(ft_itoa_base(champ.instructions[i + 1], 2, 1)))) == NULL)
		return (-1);
	j = ft_atoi_base(str, 2);
	ft_strdel(&str);
	if ((str = ft_itoa(j)) == NULL)
		return (-1);
	write(fd, str, ft_strlen(str));
	ft_strdel(&str);
	return (i + 2);
}

int				complete_ocp(t_champ champ, int fd, int *i)
{
	int				d;

	d = champ.instructions[*i - 1];
	if (d == 9 || d == 12 || d == 15)
	{
		*i = write_ind(fd, champ, *i, d);
		write(fd, "\n", 1);
		return (1);
	}
	if (d == 1)
	{
		*i = write_dir(fd, champ, *i);
		write(fd, "\n", 1);
		return (1);
	}
	return (0);
}

int				write_instruction(t_champ champ, char *ocp, int *i, int fd)
{
	unsigned int	j;
	int				d;

	j = 0;
	d = champ.instructions[*i - 2];
	while (j < ft_strlen(ocp))
	{
		if (ocp[j] == '0' && ocp[j + 1] == '1')
			*i = write_reg(fd, champ, *i);
		else if (ocp[j] == '1' && ocp[j + 1] == '1')
			*i = write_ind(fd, champ, *i, d);
		else if (ocp[j] == '1' && ocp[j + 1] == '0' && (d == 9
					|| d == 10 || d == 11 || d == 12 || d == 14 || d == 15))
			*i = write_ind(fd, champ, *i, d);
		else if (ocp[j] == '1' && ocp[j + 1] == '0')
			*i = write_dir(fd, champ, *i);
		j += 2;
		if (j + 1 < ft_strlen(ocp) && ocp[j] == '0' && ocp[j + 1] == '0')
		{
			write(fd, "\n", 1);
			return (1);
		}
		(j < 6) ? write(fd, ", ", 2) : 0;
	}
	return (1);
}
