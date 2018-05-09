/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_strlen_printing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 18:02:06 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 18:02:11 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

size_t		ls_strlen_printing(char *name)
{
	size_t		i;

	i = 0;
	while (*name)
	{
		if ((*name | 0x7F) != 0x7F)
		{
			name += sizeof(wchar_t);
			i += 2;
		}
		else
		{
			++name;
			++i;
		}
	}
	return (i);
}
