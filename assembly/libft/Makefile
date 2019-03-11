# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/03 12:20:26 by pavaucha          #+#    #+#              #
#    Updated: 2019/03/02 20:39:29 by mavui            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################
#   File name to create   #
###########################

NAME = libft.a

#########################
#   Compilation flags   #
#########################

CC = gcc

FLAGS = -Wall -Wextra -Werror

#################
#   Directory   #
#################

SRCDIR = srcs

INCDIR = includes

OBJDIR = objs

PRINTFDIR = srcs/ft_printf

###################
#   Source name   #
###################

LIBFT = ft_strlen		\
	  	ft_strdup		\
	  	ft_strcpy		\
	  	ft_strcat		\
	  	ft_strchr		\
	  	ft_strrchr		\
	  	ft_strcmp		\
	  	ft_atoi			\
	  	ft_isalpha		\
	  	ft_isdigit		\
	  	ft_isalnum		\
	  	ft_strnew		\
	  	ft_strdel		\
	  	ft_strdel_tab	\
	  	ft_strsub		\
	  	ft_strjoin		\
	  	ft_strjoin_char	\
	  	ft_strtrim		\
	  	ft_strsplit		\
	  	ft_putchar		\
	  	ft_putchar_fd	\
	  	ft_putstr		\
	  	ft_putstr_fd	\
	  	ft_putnstr		\
	  	ft_itoa_base	\
	  	ft_atoi_base	\
		ft_tablen		\
		ft_isblank		\
		ft_strlen_blank \
		ft_isprint 		\
		ft_memalloc		\
		ft_num_len 		\
		ft_power 		\
		ft_putendl 		\
		ft_strncmp 		\
		ft_strncpy 		\
		ft_strndup 		\
		ft_tolower 		\
		ft_memset 		\
		get_next_line




PRINTF = ft_printf			\
		 ft_check_flags		\
		 ft_check_type		\
		 ft_get_val			\
		 ft_wchar			\
		 ft_wchar_len		\
		 ft_wstr			\
		 ft_wstr_len		\
		 ft_percent			\
		 ft_other			\
		 ft_di				\
		 ft_di2				\
		 ft_u				\
		 ft_o				\
		 ft_o2				\
		 ft_x				\
		 ft_x2				\
		 ft_p				\
		 ft_p2				\
		 ft_c				\
		 ft_s				\
		 ft_bigs

##############
#   Source   #
##############

SRCLIBFT = $(addprefix $(SRCDIR)/, $(addsuffix .c, $(LIBFT)))

SRCPRINTF = $(addprefix $(PRINTFDIR)/$(SRCDIR)/, $(addsuffix .c, $(PRINTF)))

SRC = $(SRCLIBFT) $(SRCPRINTF)

###############
#   Objects   #
###############

OBJLIBFT = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(LIBFT)))

OBJPRINTF = $(addprefix $(PRINTFDIR)/$(OBJDIR)/, $(addsuffix .o, $(PRINTF)))

OBJ = $(OBJLIBFT) $(OBJPRINTF)

###############
#   Headers   #
###############

INCLIBFT = -I $(INCDIR)

INC = $(INCLIBFT) $(INCPRINTF)

INCFILE = $(INCDIR)/libft.h			\
		  $(INCDIR)/ft_printf.h		\
		  $(INCDIR)/get_next_line.h	\
		  $(INCDIR)/color.h

###############
#   Targets   #
###############

all: $(NAME)

$(NAME): $(OBJ) $(INCFILE)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
	@ echo "La librairie $@	\033[1;32mCreate\033[0m"

clean:
	@ rm -rf $(OBJDIR)
	@ rm -rf $(PRINTFDIR)/$(OBJDIR)
	@ echo "$@ libft		\033[1;32mOK\033[0m"

fclean: clean
	@ rm -f $(NAME)
	@ echo "$@ libft		\033[1;32mOK\033[0m"

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(FLAGS) $(INC) -c $< -o $@

$(PRINTFDIR)/$(OBJDIR)/%.o: $(PRINTFDIR)/$(SRCDIR)/%.c
	@ mkdir -p $(PRINTFDIR)/$(OBJDIR)
	@ $(CC) $(FLAGS) $(INC) -c $< -o $@

.PHONY: all clean fclean re
