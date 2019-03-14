# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pavaucha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/14 14:04:15 by pavaucha          #+#    #+#              #
#    Updated: 2019/03/14 14:04:16 by pavaucha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: asm vm dasm

re: fclean all

fclean:
	make -C assembly/ fclean
	make -C vm/ fclean
	make -C dasm/ fclean

clean:
	make -C assembly/ clean
	make -C vm/ clean
	make -C dasm/ clean

asm:
	make -C assembly/

vm:
	make -C vm/

dasm:
	make -C dasm/

.PHONY: asm vm all fclean clean dasm
