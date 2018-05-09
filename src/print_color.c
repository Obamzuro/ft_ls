/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:02:34 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:02:40 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		print_color_name_dir(t_stat_name *file)
{
	if (file->stat.st_mode & 02 && file->stat.st_mode & 01000)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLACK, ANSI_COLOR_BGREEN);
	else if (file->stat.st_mode & 02 && !(file->stat.st_mode & 01000))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLACK, ANSI_COLOR_BYELLOWN);
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_BLUE);
}

static void		print_color_name_exec(t_stat_name *file)
{
	if (file->stat.st_mode & 04000)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLACK, ANSI_COLOR_BRED);
	else if (file->stat.st_mode & 02000)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLACK, ANSI_COLOR_BCYAN);
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_RED);
}

static int		print_color_name_inner(t_stat_name *file)
{
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s", file->name);
	return (1);
}

void			print_color_name(t_stat_name *file)
{
	if (!g_params['G'] && print_color_name_inner(file))
		return ;
	if (S_ISDIR(file->stat.st_mode))
		print_color_name_dir(file);
	else if (S_ISLNK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_MAGENTA);
	else if (S_ISSOCK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_GREENN);
	else if (S_ISFIFO(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, ANSI_COLOR_YELLOWN);
	else if (S_ISBLK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLUE, ANSI_COLOR_BCYAN);
	else if (S_ISCHR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s%s",
				ANSI_COLOR_BLUE, ANSI_COLOR_BYELLOWN);
	else if (access(file->pathname, X_OK) != -1)
		print_color_name_exec(file);
	else if (print_color_name_inner(file))
		return ;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
			"%s"ANSI_COLOR_RESET, file->name);
}
