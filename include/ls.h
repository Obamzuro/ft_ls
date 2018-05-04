/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:45:32 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/04 21:26:13 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
#define LS_H
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
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "ft_printf.h"
# define IS_CURPREV(str) ((str[0] == '.') && (!str[1] || (str[1] == '.' && !str[2])))
# define MAJOR(x) (int32_t)(((uint32_t)(x) >> 24) & 0xff)
# define MINOR(x) (uint32_t)((x) & 0xffffff)
# define AM_PARAMS 4
# define PARAMS "rRal"

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

extern int		errno;
t_max_length	g_max_length;
t_buffer		g_buff;
char			*g_nameapp;

void	quicksort_name(t_stat_name **arr, int bot, int top);
void	quicksort_argv(char **argv, int bot, int top);
char	*ls_strjoin_path(const char *s1, const char *s2);

int		fill_params(int argc, char **argv);
void	print_files(int argc, char **argv, int position);
//void	print_regfiles(int argc, char **argv, int position, t_stat_name **files);
//void	print_dir(const char *path, char isrecursion);

char	check_dir(const char *path);
char	check_access(const char *path, char isrecursion);

void	reset_max_length(void);
void	fill_max_length(t_stat_name *file);

size_t	count_files(const char *path);

void	fill_stats(t_stat_name **files, const char *path, size_t *total);
void	sort_stats(t_stat_name **files, size_t amfiles);
char	print_stats(t_stat_name **files, size_t amfiles);
char	print_l_stats(t_stat_name **files, size_t amfiles);
void	free_stats(t_stat_name **files, size_t amfiles);

#endif
