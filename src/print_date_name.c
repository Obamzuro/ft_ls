/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_date_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:02:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:02:54 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int		print_date_name_long(t_stat_name *file, char *timefilestr)
{
	timefilestr[29] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s %s %s",
		timefilestr + 4, timefilestr + 24, file->name);
	return (1);
}

void			print_date_name(t_stat_name *file)
{
	time_t	timefile;
	char	*timefilestr;
	time_t	diffmodify;

	timefile = g_params['u'] ? file->stat.st_atim.tv_sec
		: file->stat.st_mtim.tv_sec;
	timefilestr = ctime(&timefile);
	diffmodify = time(0);
	diffmodify = diffmodify > timefile ?
		diffmodify - timefile : timefile - diffmodify;
	if (diffmodify > 1.557e+7)
	{
		timefilestr[11] = 0;
		if (timefilestr[20] == ' ' && print_date_name_long(file, timefilestr))
			return ;
		timefilestr[24] = 0;
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s %s %s",
				timefilestr + 4, timefilestr + 20, file->name);
		return ;
	}
	timefilestr[16] = 0;
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s ", timefilestr + 4);
	print_color_name(file);
}
