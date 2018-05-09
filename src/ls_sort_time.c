/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:34:10 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 17:25:54 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	partition_time_normal(t_stat_name **arr, int bot, int top)
{
	time_t		mid;
	char		*midname;
	t_stat_name	*temp;

	mid = arr[(bot + top) / 2]->stat.st_mtimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while ((arr[bot]->stat.st_mtimespec.tv_sec > mid) ||
				(arr[bot]->stat.st_mtimespec.tv_sec == mid &&
				ft_strcmp(arr[bot]->name, midname) < 0))
			++bot;
		while ((arr[top]->stat.st_mtimespec.tv_sec < mid) ||
				(arr[top]->stat.st_mtimespec.tv_sec == mid &&
				ft_strcmp(arr[top]->name, midname) > 0))
			--top;
		if (bot <= top)
		{
			swap_pointers((void **)(arr + bot), (void **)(arr + top));
			++bot;
			--top;
		}
	}
	free(midname);
	return (bot);
}

static int	partition_time_reverse(t_stat_name **arr, int bot, int top)
{
	time_t		mid;
	char		*midname;
	t_stat_name	*temp;

	mid = arr[(bot + top) / 2]->stat.st_mtimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while ((arr[bot]->stat.st_mtimespec.tv_sec < mid) ||
					(arr[bot]->stat.st_mtimespec.tv_sec == mid
					&& ft_strcmp(arr[bot]->name, midname) > 0))
			++bot;
		while ((arr[top]->stat.st_mtimespec.tv_sec > mid) ||
					(arr[top]->stat.st_mtimespec.tv_sec == mid
					&& ft_strcmp(arr[top]->name, midname) < 0))
			--top;
		if (bot <= top)
		{
			swap_pointers((void **)(arr + bot), (void **)(arr + top));
			++bot;
			--top;
		}
	}
	free(midname);
	return (bot);
}

void		quicksort_time_normal(t_stat_name **arr, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition_time_normal(arr, bot, top);
		quicksort_time_normal(arr, bot, mid - 1);
		quicksort_time_normal(arr, mid, top);
	}
}

void		quicksort_time_reverse(t_stat_name **arr, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition_time_reverse(arr, bot, top);
		quicksort_time_reverse(arr, bot, mid - 1);
		quicksort_time_reverse(arr, mid, top);
	}
}

void		quicksort_time(t_stat_name **arr, int bot, int top, char reverse)
{
	if (reverse)
		quicksort_time_reverse(arr, bot, top);
	else
		quicksort_time_normal(arr, bot, top);
}
