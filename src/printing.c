/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/04 21:24:22 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static size_t	print_errorfiles(int argc, char **argv, int position, t_stat_name ***files)
{
	size_t		i;
	size_t		j;
	int			ret;
	t_stat_name	*mystat;

	i = 0;
	j = 0;
	while (position < argc)
	{
		mystat = (t_stat_name *)malloc(sizeof(t_stat_name));
		ret = lstat(argv[position], &mystat->stat);
		if (!g_params['l'] && S_ISLNK(mystat->stat.st_mode))
			ret = stat(argv[position], &mystat->stat);
		if (ret == -1)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s: %s: %s\n",
					g_nameapp, argv[position], strerror(errno));
		else if (S_ISDIR(mystat->stat.st_mode))
		{
			files[1][i] = mystat;
			files[1][i]->name = argv[position];
			files[1][i]->pathname = files[1][i]->name;
			++i;
		}
		else
		{
			files[0][j] = mystat;
			files[0][j]->name = argv[position];
			files[0][j]->pathname = files[0][j]->name;
			fill_max_length(files[0][j]);
			++j;
		}
		++position;
	}
	return (j);
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
	{
		g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "total %zu\n", total);
		print_l_stats(files, amfiles);
	}
	else
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

static void	free_files_stats(t_stat_name **files[2], int size)
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

void		print_files(int argc, char **argv, int position)
{
	char			isneedprefix;
	t_stat_name		**files[2];
	int				i;
	char			first;
	size_t			regfiles;

	quicksort_argv(argv, position, argc - 1);
	isneedprefix = 0;
	if (position < argc - 1)
		isneedprefix = 1;
	files[0] = (t_stat_name **)malloc(sizeof(t_stat_name *) * (argc - position));
	files[1] = (t_stat_name **)malloc(sizeof(t_stat_name *) * (argc - position));
	i = 0;
	while (i < argc - position)
	{
		files[0][i] = 0;
		files[1][i] = 0;
		++i;
	}
	reset_max_length();
	regfiles = print_errorfiles(argc, argv, position, files);
	if (regfiles)
	{
		if (g_params['l'])
			first = print_l_stats(files[0], regfiles);
		else
			first = print_stats(files[0], regfiles);
	}
	i = 0;
	while (i < argc - position)
	{
		if (!files[1][i])
			break ;
		if (!first)
			first = 1;
		else
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "\n");
		if (isneedprefix)
			g_buff.cur = ft_snprintf(g_buff.line, g_buff.cur, "%s:\n", files[1][i]->name);
		print_dir(files[1][i]->name, 0);
		++i;
	}
//	free_files_stats(files, argc - position);
}
