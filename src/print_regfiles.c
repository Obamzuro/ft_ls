/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 17:35:34 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		fill_argv_dirs_or_regfiles(t_stat_name *mystat,
		t_counter *counter,
		char *name, t_stat_name **files[2])
{
	if (S_ISDIR(mystat->stat.st_mode) && !g_params['d'])
	{
		files[1][counter->dir] = mystat;
		files[1][counter->dir]->name = name;
		files[1][counter->dir]->pathname = name;
		++(counter->dir);
	}
	else
	{
		files[0][counter->file] = mystat;
		files[0][counter->file]->name = name;
		files[0][counter->file]->pathname = name;
		fill_max_length(files[0][counter->file]);
		++(counter->file);
	}
}

static void		print_error_param_file(char **argv, t_stat_name *mystat,
		int position)
{
	write(1, g_buff.line, g_buff.cur);
	ft_fprintf(2, "%s: %s: %s\n", g_nameapp, argv[position], strerror(errno));
	g_buff.cur = 0;
	free(mystat);
}

static size_t	fill_argv_files(int argc, char **argv,
		int position, t_stat_name **files[2])
{
	t_counter	counter;
	int			ret;
	t_stat_name	*mystat;
	struct stat	statqwe;

	counter.dir = 0;
	counter.file = 0;
	while (position < argc)
	{
		EXITZERO(mystat = (t_stat_name *)malloc(sizeof(t_stat_name)));
		ret = lstat(argv[position], &mystat->stat);
		if (ret != -1 && !g_params['l'] && S_ISLNK(mystat->stat.st_mode) &&
				stat(argv[position], &statqwe) != -1)
			ret = stat(argv[position], &mystat->stat);
		if (ret == -1)
			print_error_param_file(argv, mystat, position);
		else
			fill_argv_dirs_or_regfiles(mystat, &counter, argv[position], files);
		++position;
	}
	quicksort_name(files[1], 0, counter.dir - 1, g_params['r']);
	return (counter.file);
}

void			print_regfiles(t_stat_name **files[2], int argc,
		char **argv, int position)
{
	size_t			amregfiles;

	reset_max_length();
	amregfiles = fill_argv_files(argc, argv, position, files);
	if (amregfiles)
	{
		if (g_params['t'])
			quicksort_time(files[0], 0, amregfiles - 1, g_params['r']);
		else
			quicksort_name(files[0], 0, amregfiles - 1, 0);
		if (g_params['l'])
			print_l_stats(files[0], amregfiles);
		else
			print_stats(files[0], amregfiles);
	}
}
