/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 16:32:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 16:33:02 by obamzuro         ###   ########.fr       */
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
		while ((!reverse && ft_strcmp(arr[bot]->name, mid) < 0)
				|| (reverse && ft_strcmp(arr[bot]->name, mid) > 0))
			++bot;
		while ((!reverse && ft_strcmp(arr[top]->name, mid) > 0)
				|| (reverse && ft_strcmp(arr[top]->name, mid) < 0))
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
		while ((!reverse && ft_strcmp(arr[bot], mid) < 0) ||
				(reverse && ft_strcmp(arr[bot], mid) > 0))
			++bot;
		while ((!reverse && ft_strcmp(arr[top], mid) > 0) ||
				(reverse && ft_strcmp(arr[top], mid) < 0))
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
