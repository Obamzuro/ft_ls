/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 21:35:23 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/11 12:57:42 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void			free_files_stats(t_stat_name **files[2], int size,
		char ***argv, int flag)
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
	if (flag)
	{
		free((*argv)[0]);
		free(*argv);
	}
}

static void			fill_files_structs(t_stat_name **files[2],
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

static void			print_files_without_params(int *argc, char ***argv,
		int *position, int *flag)
{
	*argv = (char **)malloc(sizeof(char *));
	(*argv)[0] = (char *)malloc(2);
	(*argv)[0][0] = '.';
	(*argv)[0][1] = 0;
	*argc = 1;
	*position = 0;
	*flag = 1;
}

static void			print_files_beginning(int *argc, char ***argv,
		int *position, int *flag)
{
	if (!g_params['f'])
		quicksort_argv(*argv, *position, *argc - 1, 0);
	else
		g_params['a'] = 1;
	*flag = 0;
	if (*position == *argc)
		print_files_without_params(argc, argv, position, flag);
}

void				print_files(int argc, char **argv, int position)
{
	char			isneedprefix;
	int				i;
	char			first;
	t_stat_name		**files[2];
	int				flag;

	print_files_beginning(&argc, &argv, &position, &flag);
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
	free_files_stats(files, argc - position, &argv, flag);
}
