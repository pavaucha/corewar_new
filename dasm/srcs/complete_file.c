/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:32:11 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 13:57:20 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

static void	write_header(int fd, t_champ champ)
{
	int		i;

	i = -1;
	write(fd, ".name \"", 7);
	while (champ.name[++i])
		write(fd, &champ.name[i], 1);
	write(fd, "\"\n", 2);
	write(fd, ".comment \"", 10);
	i = -1;
	while (champ.comment[++i])
		write(fd, &champ.comment[i], 1);
	write(fd, "\"\n", 2);
}

static int	complete_instruct(int fd, int i)
{
	if (i == 10)
		write(fd, "ldi ", 4);
	else if (i == 11)
		write(fd, "sti ", 4);
	else if (i == 12)
		write(fd, "fork ", 5);
	else if (i == 13)
		write(fd, "lld ", 4);
	else if (i == 14)
		write(fd, "lldi ", 5);
	else if (i == 15)
		write(fd, "lfork ", 6);
	else if (i == 16)
		write(fd, "aff ", 4);
	else
		return (-1);
	return (1);
}

static int	get_instruct(int fd, int i)
{
	if (i == 1)
		write(fd, "live ", 5);
	else if (i == 2)
		write(fd, "ld ", 3);
	else if (i == 3)
		write(fd, "st ", 3);
	else if (i == 4)
		write(fd, "add ", 4);
	else if (i == 5)
		write(fd, "sub ", 4);
	else if (i == 6)
		write(fd, "and ", 4);
	else if (i == 7)
		write(fd, "or ", 3);
	else if (i == 8)
		write(fd, "xor ", 4);
	else if (i == 9)
		write(fd, "zjmp ", 5);
	else
		return (complete_instruct(fd, i));
	return (1);
}

static void	write_instruct(int fd, t_champ champ)
{
	int		i;

	i = 0;
	while (champ.instructions[i])
	{
		if ((get_instruct(fd, champ.instructions[i])) == -1)
			return ;
		i++;
		if ((get_ocp(fd, champ, &i)) == -1)
			return ;
	}
}

int			complete_file(char *str, t_champ champ)
{
	int		fd;

	fd = 0;
	if ((fd = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0600)) == -1)
	{
		ft_error(7);
		return (-1);
	}
	write_header(fd, champ);
	write_instruct(fd, champ);
	close(fd);
	return (0);
}
