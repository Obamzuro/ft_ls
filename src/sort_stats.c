/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:03:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:03:36 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		sort_stats(t_stat_name **files, size_t amfiles)
{
	if (g_params['f'])
		return ;
	if (g_params['t'])
	{
		if (g_params['u'])
			quicksort_atime(files, 0, amfiles - 1, g_params['r']);
		else
			quicksort_time(files, 0, amfiles - 1, g_params['r']);
	}
	else
		quicksort_name(files, 0, amfiles - 1, g_params['r']);
	return ;
}
