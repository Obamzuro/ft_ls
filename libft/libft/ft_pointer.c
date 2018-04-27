/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 03:47:56 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 21:35:41 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		print_nsymb(int diff, char symb)
{
	int		i;

	i = 0;
	while (i < diff)
	{
		write(1, &symb, 1);
		i++;
	}
}

static void		fix_nsize(t_special *spec, uintmax_t n, ssize_t *nsize)
{
	if (!n && !spec->precision)
		*nsize = 0;
}

static void		stabilize_width(t_special *spec, uintmax_t n, int *res)
{
	ssize_t		nsize;
	int			diffprec;
	int			diffwidth;

	diffprec = 0;
	diffwidth = 0;
	nsize = ft_unbr_size(n, 16, 0);
	fix_nsize(spec, n, &nsize);
	if ((spec->precision > 0 && spec->width <= nsize) || (
				spec->flag[zero].exist))
		write(1, "0x", 2);
	if (spec->precision > nsize)
		diffprec = spec->precision - nsize;
	nsize += diffprec;
	if (spec->width > nsize)
		diffwidth = spec->width - nsize - 2;
	if (!spec->flag[minus].exist)
		spec->flag[zero].exist && spec->precision == -1 ?
			print_nsymb(diffwidth, '0') : print_nsymb(diffwidth, ' ');
	print_nsymb(diffprec, '0');
	!spec->flag[zero].exist && !diffprec ? write(1, "0x", 2) : 1;
	n || spec->precision != 0 ? ft_uputnbr_common(n, 16, 0) : 1;
	if (spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	*res += spec->width > nsize + 2 ? spec->width : nsize + 2;
}

void			print_pointer(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;

	n = va_arg(*ap, unsigned long long int);
	stabilize_width(spec, n, res);
}
