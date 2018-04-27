/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_octal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 08:32:53 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 09:54:28 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		print_nsymb(size_t diff, char symb)
{
	size_t		i;

	i = 0;
	while (i < diff)
	{
		write(1, &symb, 1);
		i++;
	}
}

static void		fix_nsize(t_special *spec, uintmax_t n, ssize_t *nsize)
{
	if (!n)
	{
		if (!spec->precision)
		{
			if (spec->flag[sharp].exist)
				*nsize = 1;
			else
				*nsize = 0;
		}
		else if (spec->flag[sharp].exist)
			*nsize = 1;
	}
}

static void		calc_diffs(t_special *spec, uintmax_t n,
		ssize_t *nsize, t_diffs *diffs)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = ft_unbr_size(n, 8, spec->flag[sharp].exist);
	fix_nsize(spec, n, nsize);
	if (spec->flag[zero].exist && *nsize >= 2)
		if (spec->flag[sharp].exist)
			write(1, "0", 1);
	if (spec->precision > *nsize)
		diffs->diffprec = spec->precision - *nsize;
	*nsize += diffs->diffprec;
	spec->width > *nsize ? diffs->diffwidth = spec->width - *nsize : 1;
}

static void		stabilize_width(t_special *spec, uintmax_t n, int *res)
{
	ssize_t		nsize;
	t_diffs		diffs;

	calc_diffs(spec, n, &nsize, &diffs);
	if (!spec->flag[minus].exist)
		spec->flag[zero].exist && spec->precision == -1 ?
			print_nsymb(diffs.diffwidth, '0') :
			print_nsymb(diffs.diffwidth, ' ');
	print_nsymb(diffs.diffprec, '0');
	if (n || spec->precision)
	{
		if (!(spec->flag[zero].exist) && !(!n && spec->flag[sharp].exist))
			if (spec->flag[sharp].exist)
				write(1, "0", 1);
		ft_uputnbr_common(n, 8, 0);
	}
	else if (spec->flag[sharp].exist)
		write(1, "0", 1);
	if (spec->flag[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void			print_unsigned_octal(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n, res);
}
