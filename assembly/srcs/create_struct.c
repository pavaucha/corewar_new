/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:09:52 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/14 13:32:34 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_ligne	*complete_label(char *str)
{
	int			i;
	t_ligne		*nline;

	i = 0;
	if ((nline = (t_ligne*)ft_memalloc(sizeof(t_ligne) * 1)) == NULL)
		return (NULL);
	while (str[i] != ':')
		i++;
	nline->next = NULL;
	if ((nline->label = ft_memalloc((size_t)(i + 1))) == NULL)
		return (NULL);
	ft_memset(nline->instruct, 0, 6);
	ft_memset(nline->pos, 0, 3);
	nline->label = ft_strncpy(nline->label, str, (size_t)i);
	nline->ligne = NULL;
	nline->arg = NULL;
	nline->nb_loctet = 0;
	nline->nb_octet_pos = 0;
	return (nline);
}

static t_ligne	*complete_instruct(char *str)
{
	int			i;
	int			j;
	t_ligne		*nline;

	j = -1;
	i = 0;
	if ((nline = (t_ligne*)ft_memalloc(sizeof(t_ligne) * 1)) == NULL)
		return (NULL);
	nline->next = NULL;
	ft_memset(nline->instruct, 0, 6);
	nline->label = NULL;
	if ((nline->ligne = ft_strdup(str)) == NULL)
		return (NULL);
	while (j < 6)
		nline->instruct[++j] = ft_isalpha(str[i]) ? str[i++] : '\0';
	while (str[i] && ft_isblank(str[i]) == 1)
		i++;
	if ((nline->arg = ft_strdup(str + i)) == NULL)
		return (NULL);
	ft_nb_octet(nline->instruct, &nline);
	nline->nb_octet_pos = 0;
	return (nline);
}

static t_ligne	*begin_struct(char **str, int *j, int *i)
{
	t_ligne		*line;

	line = NULL;
	while (str[*i][*j] && str[*i][*j] != ':' && ft_isblank(str[*i][*j]) != 1)
		(*j)++;
	if (str[*i][*j] == ':' && str[*i][*j - 1] != '%')
	{
		*j = *j + 1;
		return (complete_label(str[*i]));
	}
	else
		*j = 0;
	while (str[*i][*j] && ft_isblank(str[*i][*j]) == 1)
		(*j)++;
	if (str[*i][*j] != '\0')
		line = complete_instruct(str[*i] + (*j));
	*j = 0;
	*i = *i + 1;
	return (line);
}

static t_ligne	*initialize_complet(char **str, int i, int j, t_ligne *line)
{
	if (i == 0 && (str[i][j] == '\0' || str[i][j] == '\t' || str[i][j] == ' '
		|| (str[i][j] == ':' && str[i][j - 1] == '%')))
	{
		j = (str[i][j - 1] == '%') ? j - 1 : j;
		while (j > 0 && str[i][j] != ':')
			j--;
		j++;
	}
	while (str[i][j] && ft_isblank(str[i][j]) == 1)
		j++;
	if (str[i][j] != '\0')
	{
		line->next = complete_instruct(str[i] + j);
		line = line->next;
	}
	return (line);
}

t_ligne			*initialize_struct(char **str, int i)
{
	t_ligne		*begin;
	t_ligne		*line;
	int			j;

	j = 0;
	line = begin_struct(str, &j, &i);
	begin = line;
	while (str[i])
	{
		while (str[i][j] && str[i][j] != ':' && ft_isblank(str[i][j]) != 1)
			j++;
		if (str[i][j] == ':' && str[i][j - 1] != '%')
		{
			line->next = complete_label(str[i]);
			line = line->next;
			j++;
		}
		else
			j = (begin->next == NULL && i == 0) ? j : 0;
		line = initialize_complet(str, i, j, line);
		i++;
		j = 0;
	}
	return (begin);
}
