/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 23:00:51 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 09:08:19 by obamzuro         ###   ########.fr       */
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

static void	print_sign(t_special *spec, intmax_t n)
{
	if (n < 0)
		write(1, "-", 1);
	else if (spec->flag[plus].exist)
		write(1, "+", 1);
	else if (spec->flag[space].exist)
		write(1, " ", 1);
}

static void	calc_diffs(t_special *spec, intmax_t n,
		ssize_t *nsize, t_diffs *diffs)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = ft_nbr_size(n, 10, 0);
	if (!n && !spec->precision)
		*nsize = 0;
	if (spec->precision > *nsize)
		diffs->diffprec = spec->precision - *nsize;
	*nsize += diffs->diffprec;
	if (spec->flag[plus].exist || n < 0 || spec->flag[space].exist)
		++*nsize;
	if (spec->width > *nsize)
		diffs->diffwidth = spec->width - *nsize;
}

static void	stabilize_width(t_special *spec, intmax_t n, int *res)
{
	ssize_t		nsize;
	t_diffs		diffs;

	calc_diffs(spec, n, &nsize, &diffs);
	if (spec->flag[minus].exist || (spec->flag[zero].exist &&
				spec->precision == -1 && (spec->flag[plus].exist ||
			n < 0 || spec->flag[space].exist)))
		print_sign(spec, n);
	if (!spec->flag[minus].exist && spec->flag[zero].exist
			&& spec->precision == -1)
		print_nsymb(diffs.diffwidth, '0');
	else if (!spec->flag[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	if (!spec->flag[minus].exist && (!spec->flag[zero].exist
				|| (spec->precision != -1 && (spec->flag[plus].exist
						|| n < 0 || spec->flag[space].exist))))
		print_sign(spec, n);
	print_nsymb(diffs.diffprec, '0');
	if (n || spec->precision)
		ft_putnbr_common(n, 10, 0);
	if (spec->flag[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_decimal(t_special *spec, va_list *ap, int *res)
{
	intmax_t	n;

	get_decimal(spec, ap, &n);
	stabilize_width(spec, n, res);
}
