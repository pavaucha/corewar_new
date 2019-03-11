/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_read_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:32:33 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 13:53:48 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

int				ft_error(int i)
{
	if (i == 0)
		ft_printf("Wrong MAGIC NUMBER\n");
	else if (i == 1)
		ft_printf("PROG_NAME_LEN too long\n");
	else if (i == 2)
		ft_printf("Wrong file format\n");
	else if (i == 3)
		ft_printf("CHAMP LEN too long\n");
	else if (i == 4)
		ft_printf("PROG_COMMENT_LEN too long\n");
	else if (i == 5)
		ft_printf("CHAMP LEN do not match with INSTRCUT LEN\n");
	else if (i == 6)
		ft_printf("Error Unknown\n");
	else if (i == 7)
		ft_printf("Can't create a new .s\n");
	return (-1);
}

static int		bytes_to_int(uint8_t *bytes, unsigned *integer)
{
	unsigned	i;
	unsigned	j;

	i = 0;
	j = 0;
	i = (bytes[0] | i) << 8;
	i = bytes[1] | i;
	j = (bytes[2] | j | i) << 8;
	j = bytes[3] | j;
	*integer = (i | j);
	if (*integer > CHAMP_MAX_SIZE)
		return (-1);
	return (1);
}

static int		check_magic(int fd, t_champ *champ)
{
	static uint8_t	magic[4] = MAGIC;
	ssize_t			ret;

	if ((ret = read(fd, champ->magic, 4)) != 4)
		return (ft_error(0));
	else if (ft_memcmp(champ->magic, magic, 4))
		return (ft_error(0));
	else
		return (0);
}

static int		complete_meta(int fd, t_champ *champ)
{
	ssize_t			ret;
	uint8_t			bytes[4];
	char			*buffer[200];

	if ((ret = read(fd, champ->name, PROG_NAME_LEN)) != PROG_NAME_LEN)
		return (ft_error(1));
	else if ((ret = read(fd, bytes, 4)) != 4)
		return (ft_error(2));
	else if ((ret = read(fd, bytes, 4)) != 4)
		return (ft_error(2));
	else if (bytes_to_int(bytes, &(champ->len)) == -1)
		return (ft_error(3));
	else if ((ret = read(fd, champ->comment, COMMENT_LEN)) != COMMENT_LEN)
		return (ft_error(4));
	else if ((ret = read(fd, bytes, 4)) != 4)
		return (ft_error(2));
	else if ((ret = read(fd, champ->instructions, champ->len)) != champ->len)
		return (ft_error(5));
	else if (read(fd, buffer, 1) != 0)
		return (ft_error(6));
	else
		return (0);
}

int				complete(int fd, t_champ *champ)
{
	int	ret;

	if ((ret = check_magic(fd, champ)) != 0)
		return (ret);
	else if ((ret = complete_meta(fd, champ)) == -1)
		return (ret);
	else
		return (0);
}
