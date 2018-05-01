# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 00:20:32 by obamzuro          #+#    #+#              #
#    Updated: 2018/05/01 19:07:51 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ls

SRCNAME = 	main.c			\
			ls_strjoin.c		\
			ls_sort.c			\

SRC = $(addprefix src/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	make -C libftprintf
	make -C libft
	gcc $(SRC) -I include -L libft -lft -L libftprintf -lftprintf -o $(NAME)
	gcc $(SRC) -g -I include -L libft -lft -L libftprintf -lftprintf -o d

%.o: %.c
	gcc -c $< -o $@

clean:
	make -C libftprintf clean
	make -C libft clean
	find . -name ".*.sw[pon" -o -name "*.o" -exec rm -f {} \;

fclean: clean
	make -C libftprintf fclean
	make -C libft fclean
	rm $(NAME)

re: fclean all
