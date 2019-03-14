# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavaucha <pavaucha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 09:44:22 by pavaucha          #+#    #+#              #
#    Updated: 2019/03/13 16:18:19 by pavaucha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

CC = cc

CFLAGS			:=	-Wall  \
					-Werror \
					-Wextra \

# OFLAGS =	-fsanitize=address	\
#			-fno-omit-frame-pointer		\
#			-fsanitize-address-use-after-scope

SOURCES = 	srcs/main.c \
			srcs/parse_file.c \
			srcs/check_line.c \
			srcs/check_label.c \
			srcs/header.c \
			srcs/err.c \
			srcs/err2.c \
			srcs/char_err.c \
			srcs/wrong_inst.c \
			srcs/wrong_params.c \
			srcs/params.c \
			srcs/tools.c \
			srcs/tools2.c \
			srcs/check_inst1.c \
			srcs/check_inst2.c \
			srcs/check_inst3.c \
			srcs/find_octet.c \
			srcs/convert_name_com.c \
			srcs/write_instruction.c \
			srcs/label.c \
			srcs/initialize_header.c \
			srcs/ft_affiche_header.c \
			srcs/swap_bits_16.c \
			srcs/ft_encoding.c \
			srcs/ft_strnew_c.c \
			srcs/fill_call_label.c \
			srcs/create_struct.c \
			srcs/ft_overflow.c \
			srcs/ft_read.c

INCLUDES =	includes/asm.h \
			includes/ft_read.h

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
