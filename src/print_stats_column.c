/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stats_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:03:11 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:43:56 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		handle_width_tty(size_t amfiles,
		size_t *columns, size_t *rows)
{
	struct winsize	ws;
	size_t			sum_name;
	size_t			tabmax;

	*rows = 1;
	*columns = amfiles;
	if (ioctl(0, TIOCGWINSZ, &ws) != 0)
		return ;
	tabmax = 8 * ((g_max_length.name / 8) + 1);
	sum_name = amfiles * tabmax;
	if (!ws.ws_col || !sum_name)
		return ;
	while (ceil((double)amfiles / *rows) * tabmax > ws.ws_col)
	{
		++(*rows);
		if (!*rows)
		{
			*rows = 0;
			*columns = 0;
			return ;
		}
	}
	*columns = ceil((double)amfiles / *rows);
}

static void		print_smooth_stats(t_stat_name **files, size_t num, char *first,
		int *lastnamesize)
{
	int				j;
	int				temp;
	int				tabmax;

	if (!*first)
	{
		print_color_name(files[num]);
		*first = 1;
		*lastnamesize = ls_strlen_printing(files[num]->name);
	}
	else
	{
		j = 0;
		tabmax = 8 * ((g_max_length.name / 8) + 1);
		temp = ceil((tabmax - *lastnamesize) / (double)8);
		if (!temp)
			temp = 1;
		while (j < temp)
		{
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\t");
			++j;
		}
		print_color_name(files[num]);
		*lastnamesize = ls_strlen_printing(files[num]->name);
	}
}

static void		print_one_stats(t_stat_name **files,
		size_t amfiles, t_iter *iter)
{
	while (iter->j < amfiles)
	{
		print_color_name(files[iter->j]);
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		++(iter->j);
	}
}

void			print_stats(t_stat_name **files, size_t amfiles)
{
	char			first;
	int				lastnamesize;
	t_iter			iter;
	t_tty_params	ttyparams;

	lastnamesize = 0;
	iter.j = 0;
	if (g_params['1'])
		print_one_stats(files, amfiles, &iter);
	handle_width_tty(amfiles, &ttyparams.columns, &ttyparams.rows);
	while (iter.j < ttyparams.rows)
	{
		first = 0;
		iter.i = 0;
		while (iter.i < ttyparams.columns)
		{
			if (iter.i * ttyparams.rows + iter.j >= amfiles)
				break ;
			print_smooth_stats(files, iter.i * ttyparams.rows + iter.j, &first,
					&lastnamesize);
			++(iter.i);
		}
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		++(iter.j);
	}
}
