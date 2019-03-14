# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 09:44:22 by pavaucha          #+#    #+#              #
#    Updated: 2019/03/07 10:45:54 by pavaucha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = reverse_cor

CC = cc

CFLAGS			:=	-Wall  \
					-Werror \
					-Wextra \

SOURCES = 	srcs/main.c \
			srcs/parsing_champ.c \
			srcs/open_read_file.c \
			srcs/complete_file.c \
			srcs/get_ocp.c \
			srcs/write_instruct.c

INCLUDES = includes/reverse.h

SRCS 			=	$(SOURCES)

OFILES			=	${SRCS:.c=.o}

all: $(NAME)

$(NAME): libft $(OFILES)
	gcc $(OFILES) $(OFLAGS) $(LIBS) libft/libft.a -o $(NAME)

%.o: %.c $(INCLUDES)
	$(CC)  $< -c $(CFLAGS) -Iincludes -Ilibft/includes -o $@

libft: libft/libft.a

libft/libft.a:
	make -C libft/

clean:
	/bin/rm -f $(OFILES)
	make -C libft/ clean

fclean: clean
	make -C libft/ fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM/

re: fclean all
