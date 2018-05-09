/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:01:35 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:01:41 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		free_stats(t_stat_name **files, size_t amfiles)
{
	size_t i;

	i = 0;
	while (i < amfiles)
	{
		free(files[i]->name);
		free(files[i]->pathname);
		free(files[i]);
		++i;
	}
	free(files);
}
