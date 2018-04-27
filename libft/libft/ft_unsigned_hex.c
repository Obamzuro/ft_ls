/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 06:53:13 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 09:18:56 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_nsymb(size_t diff, char symb)
{
	size_t		i;

	i = 0;
	while (i < diff)
	{
		write(1, &symb, 1);
		i++;
	}
}

static void	print_prefix(t_special *spec)
{
	if (spec->flag[sharp].exist)
	{
		if (spec->conversion->ascii == 'x')
			write(1, "0x", 2);
		if (spec->conversion->ascii == 'X')
			write(1, "0X", 2);
	}
}

static void	calc_diffs(t_special *spec, ssize_t *nsize,
		t_diffs *diffs, uintmax_t *n)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = ft_unbr_size(*n, 16, 0);
	if (!*n && spec->precision != -1)
		*nsize = 0;
	if (spec->precision > *nsize)
		diffs->diffprec = spec->precision - *nsize;
	*nsize += diffs->diffprec;
	if (spec->flag[sharp].exist && *n)
		*nsize += 2;
	if (spec->width > *nsize)
		diffs->diffwidth = spec->width - *nsize;
}

static void	stabilize_width(t_special *spec, uintmax_t n, int *res)
{
	ssize_t		nsize;
	t_diffs		diffs;

	calc_diffs(spec, &nsize, &diffs, &n);
	if (n && spec->precision == -1 && spec->flag[zero].exist)
		print_prefix(spec);
	if (!spec->flag[minus].exist)
	{
		if (spec->flag[zero].exist && spec->precision == -1)
			print_nsymb(diffs.diffwidth, '0');
		else
			print_nsymb(diffs.diffwidth, ' ');
	}
	if (n && (spec->precision != -1 || !spec->flag[zero].exist))
		print_prefix(spec);
	print_nsymb(diffs.diffprec, '0');
	if (n || (!n && spec->precision == -1))
		ft_uputnbr_common(n, 16, spec->conversion->ascii == 'X');
	if (spec->flag[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_unsigned_hex(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n, res);
}
