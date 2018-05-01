/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 20:45:32 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 19:38:00 by obamzuro         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include "libft.h"
# include "ft_printf.h"
# define IS_CURPREV(str) ((str[0] == '.') && (!str[1] || (str[1] == '.' && !str[2])))
# define MAJOR(x) (int32_t)(((uint32_t)(x) >> 24) & 0xff)
# define MINOR(x) (uint32_t)((x) & 0xffffff)
# define AM_PARAMS 4
# define PARAMS "rRal"

typedef enum	e_params
{
	reverse,
	recursive,
	all,
	longformat
}				t_params;

typedef struct	s_params_corr
{
//	t_params	name;
	char		ascii;
	char		exist;
}				t_params_corr;

typedef struct	s_stat_name
{
	struct stat	stat;
	char		*name;
	char		*pathname;
	char		isdir;
}				t_stat_name;

typedef struct	s_max_length
{
	int	links;
	int	login;
	int	group;
	int	size;
}				t_max_length;

extern int		errno;
t_max_length	g_max_length;
t_buffer		g_buff;

void	quicksort_name(t_stat_name **arr, int bot, int top);
char	*ls_strjoin_path(const char *s1, const char *s2);

#endif
