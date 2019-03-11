/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_name_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:37:24 by pavaucha          #+#    #+#             */
/*   Updated: 2019/03/11 15:02:55 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_nb_octet(char *str, t_ligne **nline)
{
	if (ft_strcmp(str, "live") == 0
			|| ft_strcmp(str, "add") == 0 || ft_strcmp(str, "sub") == 0)
		(*nline)->nb_loctet = 5;
	else if (ft_strcmp(str, "zjmp") == 0
			|| ft_strcmp(str, "fork") == 0 || ft_strcmp(str, "lfork") == 0)
		(*nline)->nb_loctet = 3;
	else if (ft_strcmp(str, "ld") == 0 || ft_strcmp(str, "lld") == 0)
		(*nline)->nb_loctet = (ft_is_dir((*nline)->arg) == 1) ? 5 : 7;
	else if (ft_strcmp(str, "sti") == 0
			|| ft_strcmp(str, "lldi") == 0 || ft_strcmp(str, "ldi") == 0)
		(*nline)->nb_loctet = find_size_2(nline);
	else if (ft_strcmp(str, "xor") == 0
			|| ft_strcmp(str, "or") == 0 || ft_strcmp(str, "and") == 0)
		(*nline)->nb_loctet = find_size(nline);
	else if (ft_strcmp(str, "aff") == 0)
		(*nline)->nb_loctet = 3;
	else
		(*nline)->nb_loctet = (ft_is_dir((*nline)->arg) == 0) ? 4 : 5;
}


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
	ft_memset(nline->instruct, 0, 6);
	if ((nline->label = ft_memalloc(i + 1)) == NULL)
		return (NULL);
	nline->label = ft_strncpy(nline->label, str, i);
	nline->ligne = NULL;
	nline->arg = NULL;
	nline->nb_loctet = 0;
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
	return (nline);
}

static t_ligne	*begin_struct(char **str, int *j, int *i)
{
	t_ligne		*line;

	while (str[*i][*j] && str[*i][*j] != ':' && ft_isblank(str[*i][*j]) != 1)
		(*j)++;
	if (str[*i][*j] == ':' && str[*i][*j - 1] != '%')
	{
		*j = 0;
		return (complete_label(str[*i]));
	}
	else
		*j = 0;
	while (str[*i][*j] && ft_isblank(str[*i][*j]) == 1)
		(*j)++;
	line = complete_instruct(str[*i] + (*j));
	*j = 0;
	*i = *i + 1;
	return (line);
}

static t_ligne	*initialize_struct(char **str)
{
	t_ligne		*begin;
	t_ligne		*line;
	int			i;
	int			j;

	i = 0;
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
			j = 0;
		while (str[i][j] && ft_isblank(str[i][j]) == 1)
			j++;
		if (str[i][j] != '\0')
		{
			line->next = complete_instruct(str[i] + j);
			line = line->next;
		}
		i++;
		j = 0;
	}
	return (begin);
}

static	char	*find_name(char *name)
{
	int		i;
	char	*str;

	i = 0;
	while (name[i])
		i++;
	while (name[i] != '.' && i > 0)
		i--;
	if ((str = ft_strnew((size_t)i + 4)) == NULL)
		return (NULL);
	str = ft_strncpy(str, name, (size_t)i);
	str = ft_strcat(str, ".cor");
	return (str);
}

void			convert_name_com(char **str, char *name)
{
	t_ligne		*begin;
	char		*new_n;
	t_header	head;
	t_ligne		*tmp;

	if ((new_n = find_name(name)) == NULL)
		return ;
	begin = initialize_struct(str + 2);
	head = initialize_header(str);
	tmp = begin;
/*	while (tmp != NULL)
	{
		ft_printf("label = %s\noctet = %i\ninstruct = %s\narg = %s\n\n\n", tmp->label, tmp->nb_loctet, tmp->instruct, tmp->arg);
		tmp = tmp->next;
	}*/
	find_octet(&begin, open(new_n, O_WRONLY | O_TRUNC | O_CREAT, 0600), head);
	ft_putstr("Writing output program to ");
	ft_putendl(new_n);
	ft_strdel(&new_n);
}
