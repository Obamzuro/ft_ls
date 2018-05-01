/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 23:00:51 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 18:39:40 by obamzuro         ###   ########.fr       */
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

static void	print_sign(intmax_t n)
{
	if (n < 0)
		pf_write('-');
	else if (g_flags[plus].exist)
		pf_write('+');
	else if (g_flags[space].exist)
		pf_write(' ');
}

static void	calc_diffs(t_special *spec, intmax_t n,
		ssize_t *nsize, t_diffs *diffs)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = pf_nbr_size(n, 10, 0);
	if (!n && !spec->precision)
		*nsize = 0;
	if (spec->precision > *nsize)
		diffs->diffprec = spec->precision - *nsize;
	*nsize += diffs->diffprec;
	if (g_flags[plus].exist || n < 0 || g_flags[space].exist)
		++*nsize;
	if ((ssize_t)spec->width > *nsize)
		diffs->diffwidth = spec->width - *nsize;
}

static void	stabilize_width(t_special *spec, intmax_t n)
{
	ssize_t		nsize;
	t_diffs		diffs;

	calc_diffs(spec, n, &nsize, &diffs);
	if (g_flags[minus].exist || (g_flags[zero].exist &&
				spec->precision == -1 && (g_flags[plus].exist ||
			n < 0 || g_flags[space].exist)))
		print_sign(n);
	if (!g_flags[minus].exist && g_flags[zero].exist
			&& spec->precision == -1)
		print_nsymb(diffs.diffwidth, '0');
	else if (!g_flags[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	if (!g_flags[minus].exist && (!g_flags[zero].exist
				|| (spec->precision != -1 && (g_flags[plus].exist
						|| n < 0 || g_flags[space].exist))))
		print_sign(n);
	print_nsymb(diffs.diffprec, '0');
	if (n || spec->precision)
		pf_putnbr_common(n, 10, 0);
	if (g_flags[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
//	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_decimal(t_special *spec, va_list *ap)
{
	intmax_t	n;

	get_decimal(spec, ap, &n);
	stabilize_width(spec, n);
}
