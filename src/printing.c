/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/03 22:06:16 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		print_errorfiles(int argc, char **argv, int position, t_stat_name **files)
{
	size_t	i;
	int		ret;

	i = 0;
	while (position < argc)
	{
		files[i] = (t_stat_name *)malloc(sizeof(t_stat_name));
		ret = lstat(argv[position], &files[i]->stat);
		if (!g_params['l'] && S_ISLNK(files[i]->stat.st_mode))
			ret = stat(argv[position], &files[i]->stat);
		files[i]->name = argv[position];
		files[i]->pathname = files[i]->name;
		files[i]->isdir = 0;
		if (ret == -1)
		{
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s: %s: %s\n",
					g_nameapp, argv[position], strerror(errno));
			files[i]->printignore = 1;
		}
		else if (S_ISDIR(files[i]->stat.st_mode))
		{
			files[i]->printignore = 1;
			files[i]->isdir = 1;
		}
		else
		{
			files[i]->printignore = 0;
			fill_max_length(files[i]);
		}
		++position;
		++i;
	}
}

static void		print_dir(const char *path, char isrecursion)
{
	t_stat_name		**files;
	size_t			amfiles;
	size_t			i;
	size_t			total;

	if (isrecursion)
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n%s:\n", path);
	if (!check_dir(path) || !check_access(path, isrecursion))
		return ;
	total = 0;
	reset_max_length();
	amfiles = count_files(path);
	files = (t_stat_name **)malloc(sizeof(t_stat_name *) * amfiles);
	fill_stats(files, path, &total);
	sort_stats(files, amfiles);
	if (g_params['l'])
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "total %zu\n", total);
	print_stats(files, amfiles);
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
	free_stats(files, amfiles);
}

static void	free_files_stats(t_stat_name **files, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(files[i]);
		++i;
	}
	free(files);
}

void		print_files(int argc, char **argv, int position)
{
	char			isneedprefix;
	t_stat_name		**files;
	int				i;
	char			first;

	quicksort_argv(argv, position, argc - 1);
	isneedprefix = 0;
	if (position < argc - 1)
		isneedprefix = 1;
	files = (t_stat_name **)malloc(sizeof(t_stat_name *) * (argc - position));
	reset_max_length();
	print_errorfiles(argc, argv, position, files);
	first = print_stats(files, argc - position);
	i = 0;
	while (position < argc)
	{
		if (files[i]->isdir)
		{
			if (!first)
				first = 1;
			else
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
			if (isneedprefix)
				g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s:\n", files[i]->name);
			print_dir(files[i]->name, 0);
		}
		++position;
		++i;
	}
	free_files_stats(files, i);
}
