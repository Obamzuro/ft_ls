/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/02 22:45:41 by obamzuro         ###   ########.fr       */
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
		if (ret == -1)
		{
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s: %s: %s\n",
					g_nameapp, argv[position], strerror(errno));
			argv[position][0] = 0;
		}
		++position;
		++i;
	}
}

static void		print_regfiles(int argc, char **argv, int position, t_stat_name **files)
{

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
	g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "total %zu\n", total);
	print_stats(files, amfiles);
	i = 0;
	while (i < amfiles)
	{
		if (files[i]->isdir)
			print_dir(files[i]->pathname, 1);
		++i;
	}
	free_stats(files, amfiles);
}

void		print_files(int argc, char **argv, int position)
{
	char			isneedprefix;
	t_stat_name		**files;

	quicksort_argv(argv, position, argc - 1);
	isneedprefix = 0;
	if (position < argc)
		isneedprefix = 1;
	files = (t_stat_name **)malloc(sizeof(t_stat_name *) * (position - argc + 1));
	print_errorfiles(argc, argv, position, files);
	print_regfiles(argc, argv, position, files);
	while (1)
	{
		print_dir(argv[position], 0);
		++position;
		if (position >= argc)
			break ;
		ft_snprintf(g_buff.line, g_buff.cur, "\n");
	}
}

