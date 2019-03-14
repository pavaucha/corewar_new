/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:54:14 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/07 10:32:06 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse.h"

char		*add_null(char *str)
{
	char	*tmp;

	while (ft_strlen(str) < 8)
	{
		tmp = str;
		if ((str = ft_strjoin("0", str)) == NULL)
			return (NULL);
		ft_strdel(&tmp);
	}
	return (str);
}

t_champ		ft_is_negative(t_champ champ, int i, int rep, int fd)
{
	if (champ.instructions[i] <= 127)
		return (champ);
	write(fd, "-", 1);
	while (rep > 0)
	{
		champ.instructions[i] = 255 - champ.instructions[i];
		i++;
		rep--;
	}
	champ.instructions[i - 1] += 1;
	if (champ.instructions[i - 1] == 0 && champ.instructions[i - 2] == 0)
		champ.instructions[i - 2] += 1;
	return (champ);
}

char		*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(new_s = ft_strnew(len)))
		return (NULL);
	ft_strcpy(new_s, (const char*)s1);
	ft_strcat(new_s, (const char*)s2);
	ft_strdel((void*)&s1);
	ft_strdel((void*)&s2);
	return (new_s);
}

static char	*ft_take_ocp(t_champ champ, int *i)
{
	char			*ocp;
	char			*tmp;

	if ((ocp = ft_itoa_base(champ.instructions[*i], 2, 1)) == NULL)
		return (NULL);
	if (ft_strlen(ocp) < 8)
	{
		tmp = ocp;
		if ((ocp = ft_strjoin("0", ocp)) == NULL)
			return (NULL);
		ft_strdel(&tmp);
	}
	return (ocp);
}

int			get_ocp(int fd, t_champ champ, int *i)
{
	char			*ocp;
	unsigned int	j;

	if (complete_ocp(champ, fd, i) == 1)
		return (1);
	if ((ocp = ft_take_ocp(champ, i)) == NULL)
		return (-1);
	*i = *i + 1;
	j = (unsigned int)write_instruction(champ, ocp, i, fd);
	ft_strdel(&ocp);
	return ((int)j);
}
