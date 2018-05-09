/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:45:32 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:30:17 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H
# include <stdio.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <math.h>
# include <wchar.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# define ANSI_COLOR_BLACK    "\x1b[30m"
# define ANSI_COLOR_RED      "\x1b[31m"
# define ANSI_COLOR_GREEN    "\x1b[32m"
# define ANSI_COLOR_YELLOW   "\x1b[33m"
# define ANSI_COLOR_BLUE     "\x1b[34m"
# define ANSI_COLOR_MAGENTA  "\x1b[35m"
# define ANSI_COLOR_CYAN     "\x1b[36m"
# define ANSI_COLOR_WHITE    "\x1b[36m"

# define ANSI_COLOR_BLACKN   "\e[30m"
# define ANSI_COLOR_REDN     "\e[31m"
# define ANSI_COLOR_GREENN   "\e[32m"
# define ANSI_COLOR_YELLOWN  "\e[33m"
# define ANSI_COLOR_BLUEN    "\e[34m"
# define ANSI_COLOR_MAGENTAN "\e[35m"
# define ANSI_COLOR_CYANN    "\e[36m"
# define ANSI_COLOR_WHITEN   "\e[36m"

# define ANSI_COLOR_BBLACK   "\x1b[40m"
# define ANSI_COLOR_BRED     "\x1b[41m"
# define ANSI_COLOR_BGREEN   "\x1b[42m"
# define ANSI_COLOR_BYELLOW  "\x1b[43m"
# define ANSI_COLOR_BBLUE    "\x1b[44m"
# define ANSI_COLOR_BMAGENTA "\x1b[45m"
# define ANSI_COLOR_BCYAN    "\x1b[46m"
# define ANSI_COLOR_BWHITE   "\x1b[46m"
# define ANSI_COLOR_RESET    "\x1b[0m"

# define ANSI_COLOR_BBLACKN   "\e[40m"
# define ANSI_COLOR_BREDN     "\e[41m"
# define ANSI_COLOR_BGREENN   "\e[42m"
# define ANSI_COLOR_BYELLOWN  "\e[43m"
# define ANSI_COLOR_BBLUEN    "\e[44m"
# define ANSI_COLOR_BMAGENTAN "\e[45m"
# define ANSI_COLOR_BCYANN    "\e[46m"
# define ANSI_COLOR_BWHITEN   "\e[46m"

# define ANSI_COLOR_RESET    "\x1b[0m"

# define EXITZERO(x) if (!(x)) { perror(g_nameapp); exit(EXIT_FAILURE); }
# define EXITMINONE(x) if ((x) == -1) { perror(g_nameapp); exit(EXIT_FAILURE); }
# define RETURNMINONE(x) if ((x) == -1) return (-1)
# define RETURNMINONEVOID(x) if ((x) == -1) return
# define CUR(str) ((str[0] == '.') && (!str[1] || (str[1] == '.' && !str[2])))
# define MAJOR(x) (int32_t)(((uint32_t)(x) >> 24) & 0xff)
# define MINOR(x) (uint32_t)((x) & 0xffffff)
# define AM_PARAMS 11
# define PARAMS "RGraltufgd1"

char			g_params[256];

typedef struct	s_stat_name
{
	struct stat	stat;
	char		*name;
	char		*pathname;
	char		isdir;
}				t_stat_name;

typedef struct	s_max_length
{
	int		links;
	int		login;
	int		group;
	int		size;
	int		name;
}				t_max_length;

t_max_length	g_max_length;
t_buffer		g_buff;
char			*g_nameapp;

void			reset_max_length(void);
void			fill_max_length(t_stat_name *file);

int				fill_params(int argc, char **argv);

void			print_files(int argc, char **argv, int position);
void			print_dir(const char *path, char isrecursion);
void			print_regfiles(t_stat_name **files[2], int argc,
		char **argv, int position);

void			print_chmod(t_stat_name *file);
void			print_color_name(t_stat_name *file);
void			print_date_name(t_stat_name *file);

char			fill_stats(t_stat_name ***files, const char *path,
		size_t *total);
void			sort_stats(t_stat_name **files, size_t amfiles);
void			print_stats(t_stat_name **files, size_t amfiles);
void			print_l_stats(t_stat_name **files, size_t amfiles);
void			free_stats(t_stat_name **files, size_t amfiles);

char			*ls_strjoin_path(const char *s1, const char *s2);
size_t			ls_strlen_printing(char *name);
void			quicksort_name(t_stat_name **arr, int bot,
		int top, char reverse);
void			quicksort_argv(char **argv, int bot,
		int top, char reverse);
void			quicksort_time(t_stat_name **arr, int bot,
		int top, char reverse);
void			quicksort_atime(t_stat_name **arr, int bot,
		int top, char reverse);

typedef struct	s_counter
{
	size_t	file;
	size_t	dir;
}				t_counter;

typedef struct	s_tty_params
{
	size_t	rows;
	size_t	columns;
}				t_tty_params;

typedef struct	s_iter
{
	size_t	i;
	size_t	j;
	size_t	k;
}				t_iter;

#endif
