/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:38:51 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 13:25:41 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define PRINTF_BUFF_SIZE 4096
# define AM_FLAGS 5
# define AM_SIZES 6
# define AM_CONVS 15
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stddef.h>
# include <inttypes.h>

char			pf_strstr(const char *big, const char *little);
size_t			pf_strlen(const char *s);
size_t			pf_wstrlen(const wchar_t *s);
int				pf_putchar(wchar_t c);
void			pf_putstr(const char *s, size_t size);
size_t			pf_wputstr(const wchar_t *s);
void			pf_putnbr_common(intmax_t n, char base, char top);
void			pf_uputnbr_common(uintmax_t n, char base, char top);
size_t			pf_nbr_size(intmax_t n, char base, char alternative);
size_t			pf_unbr_size(uintmax_t n, char base, char alternative);

typedef enum	e_flags
{
	minus,
	plus,
	space,
	sharp,
	zero
}				t_flags;

typedef struct	s_flags_corr
{
	char	ascii;
	char	exist;
}				t_flags_corr;

typedef enum	e_size
{
	LONG_LONG_INT,
	CHAR,
	INTMAX_T,
	SIZE_T,
	LONG_INT,
	SHORT_INT,
	INT
}				t_size;

typedef struct	s_size_corr
{
	t_size	type;
	char	*str;
	char	len;
}				t_size_corr;

struct s_conv_corr;

typedef struct	s_special
{
	size_t				width;
	ssize_t				precision;
	t_size_corr			*size;
	struct s_conv_corr	*conversion;
}				t_special;

typedef struct	s_conv_corr
{
	char	ascii;
	void	(*f)(t_special *, va_list *);
}				t_conv_corr;

typedef struct	s_diffs
{
	size_t	diffwidth;
	size_t	diffprec;
}				t_diffs;

typedef struct	s_buffer
{
	char	*line;/*[PRINTF_BUFF_SIZE];*/
	size_t	cur;
	size_t	ret;
}				t_buffer;

t_size_corr		g_sizes[AM_SIZES];
t_conv_corr		g_convs[AM_CONVS];
t_flags_corr	g_flags[AM_FLAGS];
t_buffer		g_buff;

void			fill_convs(void);
void			fill_sizes(void);
void			fill_flags(void);
void			reset_flags(void);

void			read_flags(const char **src);
size_t			ft_positive_atoi(const char **src);
ssize_t			read_precision(const char **src);
t_size_corr*	read_size(const char **src);
t_conv_corr*	read_conversion(const char **src);

void			print_decimal(t_special *spec, va_list *ap);
void			print_unsigned(t_special *spec, va_list *ap);
void			print_unsigned_hex(t_special *spec, va_list *ap);
void			print_unsigned_octal(t_special *spec, va_list *ap);
void			print_char(t_special *spec, va_list *ap);
void			print_string(t_special *spec, va_list *ap);
void			print_pointer(t_special *spec, va_list *ap);
void			get_unsigned(t_special *spec, va_list *ap, uintmax_t *n);
void			get_decimal(t_special *spec, va_list *ap, intmax_t *n);

void			pf_write(char src);
void			pf_write_tail(void);

int				ft_printf(const char *src, ...);
size_t			ft_snprintf(char *line, size_t cur, const char *src, ...);
#endif
