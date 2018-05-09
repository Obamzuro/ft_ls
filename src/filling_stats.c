/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling_stats.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:01:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:01:28 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static char	check_stat(char *name, t_stat_name ***files, size_t last)
{
	size_t i;

	if (lstat(name, &((*files)[last]->stat)) != -1 ||
		(!g_params['l'] && !g_params['R']) ||
		stat(name, &((*files)[last]->stat)) != -1)
		return (0);
	i = 0;
	while (i < last)
	{
		free((*files)[i]->pathname);
		free((*files)[i]->name);
		free((*files)[i]);
		++i;
	}
	free((*files)[i]->pathname);
	free((*files)[i]);
	free((*files));
	return (-1);
}

char		fill_stats(t_stat_name ***files, const char *path, size_t *total)
{
	DIR				*dir;
	struct dirent	*dp;
	size_t			count;
	char			*tempdir;

	count = 0;
	SMARTCHECK(dir = opendir(path));
	while ((dp = readdir(dir)) != NULL)
	{
		if (!g_params['a'] && dp->d_name[0] == '.')
			continue ;
		EXITZERO((*files)[count] = (t_stat_name *)malloc(sizeof(t_stat_name)));
		tempdir = ls_strjoin_path(path, dp->d_name);
		(*files)[count]->pathname = tempdir;
		if (check_stat(tempdir, files, count) == -1 && closedir(dir) != 1)
			return (-1);
		(*files)[count]->isdir = ((!CUR(dp->d_name) &&
					S_ISDIR((*files)[count]->stat.st_mode))) ? 1 : 0;
		(*files)[count]->name = ft_strdup(dp->d_name);
		fill_max_length((*files)[count]);
		*total += (*files)[count]->stat.st_blocks;
		++count;
	}
	closedir(dir);
	return (0);
}
