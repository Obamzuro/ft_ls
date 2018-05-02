/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 22:39:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/02 21:29:51 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int		partition(t_stat_name **arr, int bot, int top)
{
	char		*mid;
	t_stat_name	*temp;

	mid = ft_strdup(arr[(bot + top) / 2]->name);
	while (bot < top)
	{
		while (strcmp(arr[bot]->name, mid) < 0)
			++bot;
		while (strcmp(arr[top]->name, mid) > 0)
			--top;
		if (bot < top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
		if (bot == top)
		{
			++bot;
			--top;
		}
	}
	free(mid);
	return (bot);
}

void	quicksort_name(t_stat_name **arr, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition(arr, bot, top);
		quicksort_name(arr, bot, mid - 1);
		quicksort_name(arr, mid, top);
	}
}

static int		partition_argv(char **arr, int bot, int top)
{
	char		*mid;
	char		*temp;

	mid = ft_strdup(arr[(bot + top) / 2]);
	while (bot < top)
	{
		while (strcmp(arr[bot], mid) < 0)
			++bot;
		while (strcmp(arr[top], mid) > 0)
			--top;
		if (bot < top)
		{
			temp = arr[bot];
			arr[bot] = arr[top];
			arr[top] = temp;
			++bot;
			--top;
		}
		if (bot == top)
		{
			++bot;
			--top;
		}
	}
	free(mid);
	return (bot);
}

void	quicksort_argv(char **argv, int bot, int top)
{
	int mid;

	if (bot < top)
	{
		mid = partition_argv(argv, bot, top);
		quicksort_argv(argv, bot, mid - 1);
		quicksort_argv(argv, mid, top);
	}
}
