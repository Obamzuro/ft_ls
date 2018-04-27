/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 00:40:19 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 21:30:23 by obamzuro         ###   ########.fr       */
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

static void	calc_nsize(t_special *spec, uintmax_t n, ssize_t *nsize)
{
	*nsize = ft_unbr_size(n, 10, spec->flag[sharp].exist);
	if (!n)
	{
		if (!spec->precision)
			*nsize = 0;
		else if (spec->flag[sharp].exist)
			*nsize = 1;
	}
}

static void	stabilize_width(t_special *spec, uintmax_t n, int *res)
{
	ssize_t		nsize;
	size_t		i;
	size_t		diffprec;
	size_t		diffwidth;

	i = 0;
	diffprec = 0;
	diffwidth = 0;
	calc_nsize(spec, n, &nsize);
	if (spec->precision > nsize)
		diffprec = spec->precision - nsize;
	nsize += diffprec;
	if (spec->width > nsize)
		diffwidth = spec->width - nsize;
	if (!spec->flag[minus].exist &&
			spec->flag[zero].exist && spec->precision == -1)
		print_nsymb(diffwidth, '0');
	else if (!spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	print_nsymb(diffprec, '0');
	if (n || spec->precision)
		ft_uputnbr_common(n, 10, spec->conversion->ascii == 'X');
	if (spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_unsigned(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;

	get_unsigned(spec, ap, &n);
	stabilize_width(spec, n, res);
}
