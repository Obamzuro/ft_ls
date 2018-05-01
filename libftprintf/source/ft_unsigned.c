/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 00:40:19 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 18:39:17 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_nsymb(size_t diff, char symb)
{
	size_t		i;

	i = 0;
	while (i < diff)
	{
		pf_write(symb);
		i++;
	}
}

static void	calc_nsize(t_special *spec, uintmax_t n, ssize_t *nsize)
{
	*nsize = pf_unbr_size(n, 10, 0);
	if (!n && !spec->precision)
		*nsize = 0;
}

static void	stabilize_width(t_special *spec, uintmax_t n)
{
	ssize_t		nsize;
	size_t		diffprec;
	size_t		diffwidth;

	diffprec = 0;
	diffwidth = 0;
	calc_nsize(spec, n, &nsize);
	if (spec->precision > nsize)
		diffprec = spec->precision - nsize;
	nsize += diffprec;
	if ((ssize_t)spec->width > nsize)
		diffwidth = spec->width - nsize;
	if (!g_flags[minus].exist)
	{
		if (g_flags[zero].exist && spec->precision == -1)
			print_nsymb(diffwidth, '0');
		else
			print_nsymb(diffwidth, ' ');
	}
	print_nsymb(diffprec, '0');
	if (n || spec->precision)
		pf_uputnbr_common(n, 10, 0);
	if (g_flags[minus].exist)
		print_nsymb(diffwidth, ' ');
}

void		print_unsigned(t_special *spec, va_list *ap)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n);
}
