/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/08 16:34:36 by obamzuro         ###   ########.fr       */
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

static size_t	fill_argv_files(int argc, char **argv,
		int position, t_stat_name **files[2])
{
	t_counter	counter;
	int			ret;
	t_stat_name	*mystat;

	counter.dir = 0;
	counter.file = 0;
	while (position < argc)
	{
		EXITZERO(mystat = (t_stat_name *)malloc(sizeof(t_stat_name)));
		ret = lstat(argv[position], &mystat->stat);
		if (ret != -1 && !g_params['l'] && S_ISLNK(mystat->stat.st_mode))
			ret = stat(argv[position], &mystat->stat);
		if (ret == -1)
		{
//			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
//					"%s: %s: %s\n", g_nameapp, argv[position], strerror(errno));
			write(1, g_buff.line, g_buff.cur);
			fprintf(stderr, "%s: %s: %s\n", g_nameapp, argv[position], strerror(errno));
			g_buff.cur = 0;
			free(mystat);
		}
		else
			fill_argv_dirs_or_regfiles(mystat, &counter, argv[position], files);
		++position;
	}
	return (counter.file);
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
//	if ((amfiles = count_files(path)) > 0 && isrecursion)
//		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
	EXITZERO(files = (t_stat_name **)malloc(sizeof(t_stat_name *) * amfiles));
	if (fill_stats(&files, path, &total) == -1)
		return ;
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

static void		free_files_stats(t_stat_name **files[2], int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(files[0][i]);
		free(files[1][i]);
		++i;
	}
	free(files[0]);
	free(files[1]);
}

void			fill_files_structs(t_stat_name **files[2],
		int argc, int position)
{
	int i;

	EXITZERO(files[0] = (t_stat_name **)malloc(sizeof(t_stat_name *)
				* (argc - position)));
	EXITZERO(files[1] = (t_stat_name **)malloc(sizeof(t_stat_name *)
				* (argc - position)));
	i = 0;
	while (i < argc - position)
	{
		files[0][i] = 0;
		files[1][i] = 0;
		++i;
	}
}

void			print_regfiles(t_stat_name **files[2], int argc,
		char **argv, int position)
{
	size_t			amregfiles;

	reset_max_length();
	amregfiles = fill_argv_files(argc, argv, position, files);
	if (amregfiles)
	{
		if (g_params['l'])
			print_l_stats(files[0], amregfiles);
		else
			print_stats(files[0], amregfiles);
	}
}

void			print_files(int argc, char **argv, int position)
{
	char			isneedprefix;
	int				i;
	char			first;
	t_stat_name		**files[2];
	int				flag;

	if (!g_params['f'])
		quicksort_argv(argv, position, argc - 1, g_params['r']);
	else
		g_params['a'] = 1;
	flag = 0;
	if (position == argc)
	{
		argv = (char **)malloc(sizeof(char *));
		argv[0] = (char *)malloc(2);
		argv[0][0] = '.';
		argv[0][1] = 0;
		argc = 1;
		position = 0;
		flag = 1;
	}
	fill_files_structs(files, argc, position);
	print_regfiles(files, argc, argv, position);
	isneedprefix = (position < argc - 1) ? 1 : 0;
	first = files[0][0] ? 1 : 0;
	i = -1;
	while (++i < argc - position && files[1][i])
	{
		if (!first)
			first = 1;
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		if (isneedprefix)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur,
					"%s:\n", files[1][i]->name);
		print_dir(files[1][i]->name, 0);
	}
	free_files_stats(files, argc - position);
	if (flag)
	{
		free(argv[0]);
		free(argv);
	}
}
