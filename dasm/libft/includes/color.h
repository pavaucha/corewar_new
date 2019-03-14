/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 12:20:59 by pavaucha          #+#    #+#             */
/*   Updated: 2018/11/03 12:21:06 by pavaucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define RESET_COLOR "\033[0m"

/*
** Coleur de texte
*/

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

/*
** Coleur de texte avec haute intensite
*/

# define H_BLACK "\033[1;30m"
# define H_RED "\033[1;31m"
# define H_GREEN "\033[1;32m"
# define H_YELLOW "\033[1;33m"
# define H_BLUE "\033[1;34m"
# define H_MAGENTA "\033[1;35m"
# define H_CYAN "\033[1;36m"
# define H_WHITE "\033[1;37m"

/*
** Coleur de fond du texte
*/

# define B_BLACK "\033[40m"
# define B_RED "\033[41m"
# define B_GREEN "\033[42m"
# define B_YELLOW "\033[43m"
# define B_BLUE "\033[44m"
# define B_MAGENTA "\033[45m"
# define B_CYAN "\033[46m"
# define B_WHITE "\033[47m"

# include <libft.h>

void	ft_putcolor(char *color, char *str);

#endif
