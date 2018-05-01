/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 06:53:13 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 19:02:13 by obamzuro         ###   ########.fr       */
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

static void	print_prefix(t_special *spec)
{
	if (g_flags[sharp].exist)
	{
		if (spec->conversion->ascii == 'x')
		{
			pf_write('0');
			pf_write('x');
		}
		if (spec->conversion->ascii == 'X')
		{
			pf_write('0');
			pf_write('X');
		}
	}
}

static void	calc_diffs(t_special *spec, ssize_t *nsize,
		t_diffs *diffs, uintmax_t *n)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = pf_unbr_size(*n, 16, 0);
	if (!*n && spec->precision != -1)
		*nsize = 0;
	if (spec->precision > *nsize)
		diffs->diffprec = spec->precision - *nsize;
	*nsize += diffs->diffprec;
	if (g_flags[sharp].exist && *n)
		*nsize += 2;
	if ((ssize_t)spec->width > *nsize)
		diffs->diffwidth = spec->width - *nsize;
}

static void	stabilize_width(t_special *spec, uintmax_t n)
{
	ssize_t		nsize;
	t_diffs		diffs;

	calc_diffs(spec, &nsize, &diffs, &n);
	if (n && spec->precision == -1 && g_flags[zero].exist)
		print_prefix(spec);
	if (!g_flags[minus].exist)
	{
		if (g_flags[zero].exist && spec->precision == -1)
			print_nsymb(diffs.diffwidth, '0');
		else
			print_nsymb(diffs.diffwidth, ' ');
	}
	if (n && (spec->precision != -1 || !g_flags[zero].exist))
		print_prefix(spec);
	print_nsymb(diffs.diffprec, '0');
	if (n || (!n && spec->precision == -1))
		pf_uputnbr_common(n, 16, spec->conversion->ascii == 'X');
	if (g_flags[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
//	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_unsigned_hex(t_special *spec, va_list *ap)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n);
}
