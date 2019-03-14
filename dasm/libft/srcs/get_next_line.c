/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavui <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:49:52 by mavui             #+#    #+#             */
/*   Updated: 2019/02/26 15:49:58 by mavui            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static char		*ft_read(const int fd, char *str)
{
	char	*buf;
	char	*endl;
	char	*temp;
	int		ret;

	if ((buf = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))) == NULL)
	{
		buf = NULL;
		return (NULL);
	}
	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (buf[0] == '\0')
			break ;
		temp = str;
		if ((str = ft_strjoin(str, buf)) == NULL)
			return (NULL);
		ft_strdel(&temp);
		if ((endl = ft_strchr(str, '\n')) != NULL)
			break ;
	}
	ft_strdel(&buf);
	return (str);
}

static int		ft_last_line(int fd, char **line, char **gnl)
{
	int				ret;
	int				len;

	len = ft_strlen(gnl[fd]) - 1;
	while (len > 0 && (gnl[fd][len] == '\t' || gnl[fd][len] == ' '))
		len--;
	if (len > 0 && gnl[fd][len] == '\n')
	{
		ret = 0;
		while (gnl[fd][ret] && gnl[fd][ret] != '\n')
			ret++;
		if ((*line = ft_strsub(gnl[fd], 0, ret)) == NULL)
			return (-1);
		gnl[fd] = ft_strncpy(gnl[fd], gnl[fd] + ret + 1, ft_strlen(gnl[fd]));
		return (1);
	}
	return (-1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*gnl[OPEN_MAX] = {NULL};
	int				ret;

	if (BUFF_SIZE < 1 || read(fd, NULL, 0) == -1 || line == NULL
			|| fd > OPEN_MAX)
		return (-1);
	if (!gnl[fd] && (gnl[fd] = ft_strnew(1)) == NULL)
		return (-1);
	if ((gnl[fd] = ft_read(fd, gnl[fd])) == NULL)
		return (-1);
	if (ft_last_line(fd, line, gnl) == 1)
		return (2);
	if (gnl[fd][0] != '\0')
	{
		ret = 0;
		while (gnl[fd][ret] != '\n' && gnl[fd][ret] != '\0')
			ret++;
		if ((*line = ft_strsub(gnl[fd], 0, ret)) == NULL)
			return (-1);
		gnl[fd][ret] == '\0' ? ret-- : ret;
		gnl[fd] = ft_strncpy(gnl[fd], gnl[fd] + ret + 1, ft_strlen(gnl[fd]));
		return (1);
	}
	ft_strdel(&gnl[fd]);
	return (0);
}
