# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 00:20:32 by obamzuro          #+#    #+#              #
#    Updated: 2018/04/25 21:12:34 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ls

SRC = main.c\
	  sort.c

all: $(NAME)

$(NAME): $(SRC)
	gcc $(SRC) -I libft/libft -L libft -lftprintf -o $(NAME)

d: $(SRC)
	gcc -g $(SRC) -I libft/libft -L libft -lftprintf -o d

clean:
	rm -rf main.o

fclean:
	rm $(NAME)

re: fclean all d
