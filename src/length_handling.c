/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:01:47 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:01:55 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		reset_max_length(void)
{
	g_max_length.links = 0;
	g_max_length.login = 0;
	g_max_length.group = 0;
	g_max_length.size = 0;
	g_max_length.name = 0;
}

void		fill_max_length(t_stat_name *file)
{
	int	temp;

	if (g_params['l'])
	{
		if ((temp = ft_nbr_size(file->stat.st_nlink)) > g_max_length.links)
			g_max_length.links = temp;
		if ((temp = ft_strlen(getpwuid(file->stat.st_uid)->pw_name))
				> g_max_length.login)
			g_max_length.login = temp;
		if ((temp = ft_strlen(getgrgid(file->stat.st_gid)->gr_name))
				> g_max_length.group)
			g_max_length.group = temp;
		if (S_ISBLK(file->stat.st_mode) || S_ISCHR(file->stat.st_mode))
			(g_max_length.size < 8) ? g_max_length.size = 8 : 0;
		else if ((temp = ft_nbr_size(file->stat.st_size)) > g_max_length.size)
			g_max_length.size = temp;
	}
	if ((temp = ft_strlen(file->name)) > g_max_length.name)
		g_max_length.name = temp;
}
