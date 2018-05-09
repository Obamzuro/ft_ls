# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/18 00:20:32 by obamzuro          #+#    #+#              #
#    Updated: 2018/05/09 18:32:56 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCNAME = 	main.c					\
			parser.c				\
			print_chmod.c			\
			print_color.c			\
			print_date_name.c		\
			print_dirs.c			\
			print_files.c			\
			print_regfiles.c		\
			print_stats_column.c	\
			print_stats_l.c			\
			sort_stats.c			\
			filling_stats.c			\
			free_stats.c			\
			length_handling.c		\
			ls_sort_atime.c			\
			ls_sort_name.c			\
			ls_sort_time.c			\
			ls_strjoin.c			\
			ls_strlen_printing.c	\



SRC = $(addprefix src/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	make -C libftprintf/
	gcc $(OBJ) -I include -L libft -lft -L libftprintf -lftprintf -o $(NAME)

%.o: %.c
	gcc -g -I include -c $< -o $@

clean:
	make -C libft/ clean
	make -C libftprintf/ clean
	find . -name ".*.sw[klmpon]" -o -name "*.o" -exec rm -rf {} \;

fclean: clean
	make -C libft/ fclean
	make -C libftprintf/ fclean
	rm -rf $(NAME)

re: fclean all
