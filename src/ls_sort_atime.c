/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_atime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:33:52 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:01:59 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	partition_atime_normal(t_stat_name **arr, int bot, int top)
{
	time_t		mid;
	char		*midname;
	t_stat_name	*temp;

	mid = arr[(bot + top) / 2]->stat.st_atimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while ((arr[bot]->stat.st_atimespec.tv_sec > mid) ||
				(arr[bot]->stat.st_atimespec.tv_sec == mid
				&& ft_strcmp(arr[bot]->name, midname) < 0))
			++bot;
		while ((arr[top]->stat.st_atimespec.tv_sec < mid) ||
				(arr[top]->stat.st_atimespec.tv_sec == mid
				&& ft_strcmp(arr[top]->name, midname) > 0))
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

static int	partition_atime_reverse(t_stat_name **arr, int bot, int top)
{
	time_t		mid;
	char		*midname;
	t_stat_name	*temp;

	mid = arr[(bot + top) / 2]->stat.st_atimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while ((arr[bot]->stat.st_atimespec.tv_sec < mid) ||
					(arr[bot]->stat.st_atimespec.tv_sec == mid
					&& ft_strcmp(arr[bot]->name, midname) > 0))
			++bot;
		while ((arr[top]->stat.st_atimespec.tv_sec > mid) ||
					(arr[top]->stat.st_atimespec.tv_sec == mid
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

void		quicksort_atime_normal(t_stat_name **arr, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition_atime_normal(arr, bot, top);
		quicksort_atime_normal(arr, bot, mid - 1);
		quicksort_atime_normal(arr, mid, top);
	}
}

void		quicksort_atime_reverse(t_stat_name **arr, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition_atime_reverse(arr, bot, top);
		quicksort_atime_reverse(arr, bot, mid - 1);
		quicksort_atime_reverse(arr, mid, top);
	}
}

void		quicksort_atime(t_stat_name **arr, int bot, int top, char reverse)
{
	if (reverse)
		quicksort_atime_reverse(arr, bot, top);
	else
		quicksort_atime_normal(arr, bot, top);
}
