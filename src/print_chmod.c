/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chmod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:02:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:04:03 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		print_acl(t_stat_name *file)
{
	acl_t		acl;
	acl_entry_t	entry;

	if ((listxattr(file->pathname, 0, 0, XATTR_NOFOLLOW)) > 0)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "@");
	else if ((acl = acl_get_link_np(file->pathname, ACL_TYPE_EXTENDED)))
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "+");
		free(acl);
	}
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, " ");
}

static void		print_chmod_exec_sticky(t_stat_name *file,
		size_t bit, mode_t mode)
{
	if (mode & bit)
		if (mode & 0x200)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "t");
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "x");
	else if (mode & 0x200)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "T");
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
}

static void		print_chmod_exec(t_stat_name *file, int order, size_t bit)
{
	mode_t	mode;

	mode = file->stat.st_mode;
	if (order == 2 || order == 1)
	{
		if (mode & bit)
			if (mode & (0x200 << order))
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "s");
			else
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "x");
		else if (mode & (0x200 << order))
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "S");
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
	}
	else
		print_chmod_exec_sticky(file, bit, mode);
}

static void		print_chmod_access(t_stat_name *file)
{
	mode_t	mode;
	int		i;
	size_t	j;
	size_t	temp;

	mode = file->stat.st_mode;
	i = 8;
	while (i >= 0)
	{
		temp = 1;
		temp <<= i;
		if (!(i % 3))
			print_chmod_exec(file, i / 3, temp);
		else if (mode & temp)
		{
			if ((i % 3) == 1)
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "w");
			else if ((i % 3) == 2)
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "r");
		}
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
		--i;
	}
}

void			print_chmod(t_stat_name *file)
{
	if (S_ISLNK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "l");
	else if (S_ISDIR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "d");
	else if (S_ISCHR(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "c");
	else if (S_ISBLK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "b");
	else if (S_ISSOCK(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "s");
	else if (S_ISFIFO(file->stat.st_mode))
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "p");
	else
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "-");
	print_chmod_access(file);
	print_acl(file);
}
