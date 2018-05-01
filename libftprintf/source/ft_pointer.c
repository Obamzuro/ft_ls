/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 03:47:56 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/30 21:39:48 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_nsymb(int diff, char symb)
{
	int		i;

	i = 0;
	while (i < diff)
	{
		pf_write(1, &symb, 1);
		i++;
	}
}

static void		fix_nsize(t_special *spec, uintmax_t n, ssize_t *nsize)
{
	if (!n && !spec->precision)
		*nsize = 0;
}

static void		stabilize_width(t_special *spec, uintmax_t n)
{
	ssize_t		nsize;
	int			diffprec;
	int			diffwidth;

	diffprec = 0;
	diffwidth = 0;
	nsize = pf_unbr_size(n, 16, 0);
	fix_nsize(spec, n, &nsize);
	if ((spec->precision > 0 && spec->width <= nsize) || (
				g_flags[zero].exist))
	{
		pf_write('0');
		pf_write('x');
	}
	if (spec->precision > nsize)
		diffprec = spec->precision - nsize;
	nsize += diffprec;
	if (spec->width > nsize)
		diffwidth = spec->width - nsize - 2;
	if (!g_flags[minus].exist)
		g_flags[zero].exist && spec->precision == -1 ?
			print_nsymb(diffwidth, '0') : print_nsymb(diffwidth, ' ');
	print_nsymb(diffprec, '0');
	if (!g_flags[zero].exist && !diffprec)
	{
		pf_write('0');
		pf_write('x');
	}
	n || spec->precision != 0 ? pf_uputnbr_common(n, 16, 0) : 1;
	if (g_flags[minus].exist)
		print_nsymb(diffwidth, ' ');
//	*res += spec->width > nsize + 2 ? spec->width : nsize + 2;
}

void			print_pointer(t_special *spec, va_list *ap)
{
	uintmax_t	n;

	n = va_arg(*ap, unsigned long long int);
	stabilize_width(spec, n);
}
