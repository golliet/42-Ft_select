# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: golliet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 15:26:08 by golliet           #+#    #+#              #
#    Updated: 2018/02/21 09:59:37 by golliet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = ft_select

SRC = main.c list.c display.c del.c sig.c

OBJ = $(SRC:.c=.o)

FLAG = -Werror -Wextra -Wall -ltermcap

all: $(NAME)

$(NAME) : $(OBJ)
	echo "\033[1;31m"Compilation"\033[0m"
	make -C libft/
	gcc -o $(NAME) $(FLAG) $(OBJ) libft/libft.a

clean :
	echo "\033[1;35m"Cleaning"\033[0m"
	rm -f $(OBJ)
	make clean -C libft/

fclean :
	echo "\033[1;35m"Cleaning"\033[0m"
	rm -f $(OBJ)
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all
