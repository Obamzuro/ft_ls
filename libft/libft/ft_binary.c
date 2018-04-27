/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 06:53:13 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/21 18:00:31 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_uputnbr_binary(uintmax_t n)
{
	uintmax_t	j;
	uintmax_t	dop;
	int			a;
	size_t		i;
	size_t		temp;

	j = 1;
	dop = n;
	i = 0;
	while (dop / 2)
	{
		j *= 2;
		dop /= 2;
		++i;
	}
	temp = i;
	while (i++ < 8)
		write(1, "-", 1);
	i = 0;
	while (j)
	{
		a = n / j % 2;
		if (a)
		{
			if (!(temp % 3))
				a = 'x';
			else if (temp % 3 == 1)
				a = 'w';
			else if (temp % 3 == 2)
				a = 'r';
		}
		else
			a = '-';
		write(1, &a, 1);
		j /= 2;
		--temp;
	}
}

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
		write(1, "0b", 2);
}

static void	calc_diffs(t_special *spec, ssize_t *nsize,
		t_diffs *diffs, uintmax_t *n)
{
	diffs->diffprec = 0;
	diffs->diffwidth = 0;
	*nsize = ft_unbr_size(*n, 2, 0);
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
		ft_uputnbr_binary(n);
	if (spec->flag[minus].exist)
		print_nsymb(diffs.diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_binary(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n, res);
}
