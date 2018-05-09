/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stats_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:03:21 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:03:26 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	print_link(t_stat_name *file)
{
	char	*pathfile;
	size_t	lim;
	ssize_t	ret;

	if (!S_ISLNK(file->stat.st_mode))
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		return ;
	}
	lim = 2;
	EXITZERO(pathfile = malloc(sizeof(char) * lim));
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " -> ");
	while ((ret = readlink(file->pathname, pathfile, lim - 1)) == lim - 1)
	{
		free(pathfile);
		lim *= 2;
		EXITZERO(pathfile = malloc(sizeof(char) * lim));
	}
	pathfile[ret] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, pathfile);
	free(pathfile);
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
}

static void	print_minmaj(t_stat_name *file)
{
	int32_t	minor;
	int32_t	major;

	minor = MINOR(file->stat.st_rdev);
	major = MAJOR(file->stat.st_rdev);
	if (minor > 255 || minor < 0)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
				" %3d, 0x%08x ", major, minor);
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
				" %3d, %3d ", major, minor);
}

void		print_l_stats(t_stat_name **files, size_t amfiles)
{
	size_t	i;

	i = 0;
	while (i < amfiles)
	{
		print_chmod(files[i]);
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d ",
				g_max_length.links, files[i]->stat.st_nlink);
		if (!g_params['g'])
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%-*s  ",
			g_max_length.login, getpwuid(files[i]->stat.st_uid)->pw_name);
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%-*s ",
				g_max_length.group, getgrgid(files[i]->stat.st_gid)->gr_name);
		if (S_ISCHR(files[i]->stat.st_mode) || S_ISBLK(files[i]->stat.st_mode))
			print_minmaj(files[i]);
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " %*d ",
				g_max_length.size, files[i]->stat.st_size);
		print_date_name(files[i]);
		print_link(files[i]);
		++i;
	}
}
