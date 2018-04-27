/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 11:38:42 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/21 18:21:53 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 100000000
# define SMARTCHECK(x) if (!(x)) return (-1)
# define AM_FLAGS 5
# define AM_SIZES 6
# define AM_CONVS 16
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <stddef.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_gnl_list
{
	char				buf[BUFF_SIZE + 1];
	int					fd;
	int					last;
	struct s_gnl_list	*next;
}				t_gnl_list;

void			*ft_memset(void *a, int b, size_t c);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_wstrlen(const wchar_t *s);
size_t			ft_wstrlen_total(const wchar_t *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, const char *s2);
char			*ft_strjoin_path(char const *s1, const char *s2);
char			*ft_strtrim(const char *s);
char			**ft_strsplit(const char *s, char c);
char			*ft_itoa(int n);
int				ft_putchar(wchar_t c);
size_t			ft_putstr(const char *s, size_t size);
size_t			ft_wputstr(const wchar_t *s, size_t size);
void			ft_putendl(const char *s);
void			ft_putnbr(int n);
int				ft_putchar_fd(wchar_t c, int fd);
size_t			ft_putstr_fd(const char *s, int fd, size_t size);
size_t			ft_wputstr_fd(const wchar_t *s, int fd, size_t size);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(const void *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t			ft_ccount(const char *s, char c);
size_t			ft_wcount(const char *s, char c);
int				ft_is_prime(int nb);
size_t			ft_list_size(t_list *begin_list);
t_list			*ft_list_last(t_list *begin_list);
char			*ft_strcpy_gnl(char *dst, const char *src);
int				get_next_line(const int fd, char **line);
void			ft_putnbr_common(intmax_t n, char base, char top);
void			ft_uputnbr_common(uintmax_t n, char base, char top);
void			ft_putnbr_fd_common(intmax_t n, int fd, char base, char top);
void			ft_uputnbr_fd_common(uintmax_t n, int fd, char base, char top);
size_t			ft_nbr_size(intmax_t n, char base, char alternative);
size_t			ft_unbr_size(uintmax_t n, char base, char alternative);
char			*ft_itoa_base(intmax_t n, char base);
void			print_ft_itoa_base(intmax_t n, char base);

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
	t_flags flag;
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
	t_size	size;
	char	*spec;
}				t_size_corr;

struct s_conv_corr;

typedef struct	s_special
{
	t_flags_corr		flag[AM_FLAGS];
	int					width;
	ssize_t				precision;
	t_size_corr			*size;
	struct s_conv_corr	*conversion;
}				t_special;

typedef struct	s_conv_corr
{
	char	ascii;
	void	(*f)(t_special *, va_list *, int *);
}				t_conv_corr;

typedef struct	s_diffs
{
	size_t	diffwidth;
	size_t	diffprec;
}				t_diffs;

void			print_decimal(t_special *spec, va_list *ap, int *res);
void			print_unsigned(t_special *spec, va_list *ap, int *res);
void			print_unsigned_hex(t_special *spec, va_list *ap, int *res);
void			print_unsigned_octal(t_special *spec, va_list *ap, int *res);
void			print_char(t_special *spec, va_list *ap, int *res);
void			print_string(t_special *spec, va_list *ap, int *res);
void			print_pointer(t_special *spec, va_list *ap, int *res);
void			print_binary(t_special *spec, va_list *ap, int *res);
void			get_unsigned(t_special *spec, va_list *ap, uintmax_t *n);
void			get_decimal(t_special *spec, va_list *ap, intmax_t *n);

void			fill_convs(void);
void			fill_convs_plus(void);
void			fill_sizes(void);
void			fill_flags(t_flags_corr *flag);

char			read_flags(const char **src, t_flags_corr *flag);
int				ft_atoi_pf(const char **src, char *error);
char			read_width(const char **src, int *width, va_list *ap);
char			read_precision(const char **src, ssize_t *precision, va_list *ap);
char			read_size(const char **src, t_size_corr **size);

t_size_corr g_sizes[AM_SIZES];
t_conv_corr g_convs[AM_CONVS];

int				ft_printf(const char *src, ...);
#endif
