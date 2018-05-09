/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 17:34:05 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:03:02 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static size_t	count_files(const char *path)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			count;

	dir = opendir(path);
	count = 0;
	if (dir == NULL)
		return (0);
	while ((dp = readdir(dir)) != NULL)
	{
		if (!(!g_params['a'] && dp->d_name[0] == '.'))
			++count;
	}
	closedir(dir);
	return (count);
}

static void		print_dir_rec(t_stat_name **files, size_t amfiles)
{
	int i;

	if (g_params['R'])
	{
		i = 0;
		while (i < amfiles)
		{
			if (files[i]->isdir)
				print_dir(files[i]->pathname, 1);
			++i;
		}
	}
}

static char		check_dir(const char *path)
{
	DIR			*dir;
	char		*slash;

	dir = opendir(path);
	if (!dir)
	{
		write(1, g_buff.line, g_buff.cur);
		slash = ft_strrchr(path, '/');
		if (slash)
			ft_fprintf(2, "%s: %s: %s\n", g_nameapp,
					slash + 1, strerror(errno));
		else
			ft_fprintf(2, "%s: %s: %s\n", g_nameapp,
					path, strerror(errno));
		g_buff.cur = 0;
		return (0);
	}
	closedir(dir);
	return (1);
}

void			print_dir(const char *path, char isrecursion)
{
	t_stat_name		**files;
	size_t			amfiles;
	size_t			total;

	if (isrecursion)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n%s:\n", path);
	if (!check_dir(path))
		return ;
	total = 0;
	reset_max_length();
	amfiles = count_files(path);
	if (!amfiles)
		return ;
	EXITZERO(files = (t_stat_name **)malloc(sizeof(t_stat_name *) * amfiles));
	RETURNMINONEVOID(fill_stats(&files, path, &total));
	sort_stats(files, amfiles);
	if (g_params['l'] && amfiles)
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "total %zu\n", total);
		print_l_stats(files, amfiles);
	}
	else
		print_stats(files, amfiles);
	print_dir_rec(files, amfiles);
	free_stats(files, amfiles);
}
