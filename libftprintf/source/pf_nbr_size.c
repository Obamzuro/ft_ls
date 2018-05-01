/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:26:34 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 13:26:34 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_nbr_size(intmax_t n, char base, char alternative)
{
	size_t i;

	i = 1;
	while (n / base)
	{
		++i;
		n /= base;
	}
	if (alternative)
	{
		if (base == 8)
			++i;
		else if (base == 16)
			i += 2;
	}
	return (i);
}

size_t	pf_unbr_size(uintmax_t n, char base, char alternative)
{
	size_t i;

	i = 1;
	while (n / base)
	{
		++i;
		n /= base;
	}
	if (alternative)
	{
		if (base == 8)
			++i;
		else if (base == 16)
			i += 2;
	}
	return (i);
}
