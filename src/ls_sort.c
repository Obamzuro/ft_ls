/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 22:39:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/08 20:14:41 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	partition(t_stat_name **arr, int bot, int top, char reverse)
{
	char		*mid;
	t_stat_name	*temp;

	mid = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while ((!reverse && strcmp(arr[bot]->name, mid) < 0)
				|| (reverse && strcmp(arr[bot]->name, mid) > 0))
			++bot;
		while ((!reverse && strcmp(arr[top]->name, mid) > 0)
				|| (reverse && strcmp(arr[top]->name, mid) < 0))
			--top;
		if (bot <= top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
	}
	free(mid);
	return (bot);
}

void		quicksort_name(t_stat_name **arr, int bot, int top, char reverse)
{
	int mid;

	if (bot < top)
	{
		mid = partition(arr, bot, top, reverse);
		quicksort_name(arr, bot, mid - 1, reverse);
		quicksort_name(arr, mid, top, reverse);
	}
}

static int	partition_argv(char **arr, int bot, int top, char reverse)
{
	char		*mid;
	char		*temp;

	mid = ft_strdup(arr[(bot + top) / 2]);
	while (bot < top)
	{
		while ((!reverse && strcmp(arr[bot], mid) < 0) ||
				(reverse && strcmp(arr[bot], mid) > 0))
			++bot;
		while ((!reverse && strcmp(arr[top], mid) > 0) ||
				(reverse && strcmp(arr[top], mid) < 0))
			--top;
		if (bot <= top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
	}
	free(mid);
	return (bot);
}

void		quicksort_argv(char **argv, int bot, int top, char reverse)
{
	int mid;

	if (bot < top)
	{
		mid = partition_argv(argv, bot, top, reverse);
		quicksort_argv(argv, bot, mid - 1, reverse);
		quicksort_argv(argv, mid, top, reverse);
	}
}

static int	partition_time(t_stat_name **arr, int bot, int top, char reverse)
{
	time_t		mid;
	char		*midname;
	t_stat_name	*temp;

	mid = arr[(bot + top) / 2]->stat.st_mtimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while (((!reverse && arr[bot]->stat.st_mtimespec.tv_sec > mid) ||
				(!reverse && arr[bot]->stat.st_mtimespec.tv_sec == mid && ft_strcmp(arr[bot]->name, midname) < 0))
				|| ((reverse && arr[bot]->stat.st_mtimespec.tv_sec < mid)) ||
					(reverse && arr[bot]->stat.st_mtimespec.tv_sec == mid && ft_strcmp(arr[bot]->name, midname) > 0))
			++bot;
		while (((!reverse && arr[top]->stat.st_mtimespec.tv_sec < mid) ||
				(!reverse && arr[top]->stat.st_mtimespec.tv_sec == mid && ft_strcmp(arr[top]->name, midname) > 0))
				|| ((reverse && arr[top]->stat.st_mtimespec.tv_sec > mid)) ||
					(reverse && arr[top]->stat.st_mtimespec.tv_sec == mid && ft_strcmp(arr[top]->name, midname) < 0))
			--top;
		if (bot <= top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
	}
	free(midname);
	return (bot);
}

void		quicksort_time(t_stat_name **arr, int bot, int top, char reverse)
{
	int mid;

	if (bot < top)
	{
		mid = partition_time(arr, bot, top, reverse);
		quicksort_time(arr, bot, mid - 1, reverse);
		quicksort_time(arr, mid, top, reverse);
	}
}

static int	partition_atime(t_stat_name **arr, int bot, int top, char reverse)
{
	time_t		mid;
	t_stat_name	*temp;
	char		*midname;

	mid = arr[(bot + top) / 2]->stat.st_atimespec.tv_sec;
	midname = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot <= top)
	{
		while (((!reverse && arr[bot]->stat.st_atimespec.tv_sec > mid) ||
				(!reverse && arr[bot]->stat.st_atimespec.tv_sec == mid && ft_strcmp(arr[bot]->name, midname) < 0))
				|| ((reverse && arr[bot]->stat.st_atimespec.tv_sec < mid)) ||
					(reverse && arr[bot]->stat.st_atimespec.tv_sec == mid && ft_strcmp(arr[bot]->name, midname) > 0))
			++bot;
		while (((!reverse && arr[top]->stat.st_atimespec.tv_sec < mid) ||
				(!reverse && arr[top]->stat.st_atimespec.tv_sec == mid && ft_strcmp(arr[top]->name, midname) > 0))
				|| ((reverse && arr[top]->stat.st_atimespec.tv_sec > mid)) ||
					(reverse && arr[top]->stat.st_atimespec.tv_sec == mid && ft_strcmp(arr[top]->name, midname) < 0))
			--top;
		if (bot <= top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
	}
	free(midname);
	return (bot);
}

void		quicksort_atime(t_stat_name **arr, int bot, int top, char reverse)
{
	int mid;

	if (bot < top)
	{
		mid = partition_atime(arr, bot, top, reverse);
		quicksort_atime(arr, bot, mid - 1, reverse);
		quicksort_atime(arr, mid, top, reverse);
	}
}
