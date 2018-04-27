#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/20 11:09:03 by obamzuro          #+#    #+#              #
#    Updated: 2018/04/20 18:47:47 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_memset.c				\
	  ft_bzero.c				\
	  ft_memcpy.c				\
	  ft_memccpy.c				\
	  ft_memmove.c				\
	  ft_memchr.c				\
	  ft_memcmp.c				\
	  ft_strlen.c				\
	  ft_strdup.c				\
	  ft_strcpy.c				\
	  ft_strncpy.c				\
	  ft_strcat.c				\
	  ft_strncat.c				\
	  ft_strlcat.c				\
	  ft_strchr.c				\
	  ft_strrchr.c				\
	  ft_strstr.c				\
	  ft_strnstr.c				\
	  ft_strcmp.c				\
	  ft_strncmp.c				\
	  ft_atoi.c					\
	  ft_isalpha.c				\
	  ft_isdigit.c				\
	  ft_isalnum.c				\
	  ft_isascii.c				\
	  ft_isprint.c				\
	  ft_toupper.c				\
	  ft_tolower.c				\
	  ft_memalloc.c				\
	  ft_memdel.c				\
	  ft_strnew.c				\
	  ft_strdel.c				\
	  ft_strclr.c				\
	  ft_striter.c				\
	  ft_striteri.c				\
	  ft_strmap.c				\
	  ft_strmapi.c				\
	  ft_strequ.c				\
	  ft_strnequ.c				\
	  ft_strsub.c				\
	  ft_strjoin.c				\
	  ft_strtrim.c				\
	  ft_strsplit.c				\
	  ft_itoa.c					\
	  ft_putchar.c				\
	  ft_putstr.c				\
	  ft_putendl.c				\
	  ft_putnbr.c				\
	  ft_putchar_fd.c			\
	  ft_putstr_fd.c			\
	  ft_putendl_fd.c			\
	  ft_putnbr_fd.c			\
	  ft_lstnew.c				\
	  ft_lstdelone.c			\
	  ft_lstdel.c				\
	  ft_lstadd.c				\
	  ft_lstiter.c				\
	  ft_lstmap.c				\
	  ft_ccount.c				\
	  ft_wcount.c				\
	  ft_is_prime.c				\
	  ft_list_size.c			\
	  ft_list_last.c			\
	  ft_strcpy_gnl.c			\
	  get_next_line.c			\
	  ft_nbr_size.c				\
	  ft_itoa_base.c			\
	  ft_printf.c				\
	  ft_decimal.c				\
	  ft_unsigned.c				\
	  ft_unsigned_octal.c		\
	  ft_unsigned_hex.c			\
	  ft_char.c					\
	  ft_string.c				\
	  ft_pointer.c				\
	  ft_getvarg.c				\
	  ft_fillglob.c				\
	  ft_printf_plus.c			\
	  ft_binary.c

SRCDIRS = $(addprefix libft/, $(SRC))

OBJECT = $(SRCDIRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

%.o:%.c
	gcc -Wall -Wextra -Werror -o $@ -c $< -I libft

mai:
	gcc main.c -I libft -L . -lftprintf

clean:
	rm -f $(OBJECT)
	find . -name ".*.sw[pon]" -exec rm -f {} +

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette
