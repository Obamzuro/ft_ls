/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:07:42 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 19:02:27 by obamzuro         ###   ########.fr       */
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

static void	stabilize_width(t_special *spec, uintmax_t n)
{
	ssize_t		nsize;
	size_t		diffwidth;

	diffwidth = 0;
	nsize = 1;
	if ((ssize_t)spec->width > nsize)
		diffwidth = spec->width - nsize;
	if (!g_flags[minus].exist && g_flags[zero].exist)
		print_nsymb(diffwidth, '0');
	else if (!g_flags[minus].exist)
		print_nsymb(diffwidth, ' ');
	if (spec->conversion->ascii == 'C')
		nsize = pf_putchar(n);
	else
		pf_write(n);
	if (g_flags[minus].exist)
		print_nsymb(diffwidth, ' ');
//	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_char(t_special *spec, va_list *ap)
{
	uintmax_t	n;
	char		ret;

	ret = 0;
	if (spec->conversion->ascii == 'c' && spec->size->type == LONG_INT)
	{
		ret = 1;
		spec->conversion->ascii = 'C';
	}
	if (spec->conversion->ascii == '%')
		n = '%';
	else
		n = va_arg(*ap, unsigned int);
	stabilize_width(spec, n);
	if (ret)
		spec->conversion->ascii = 'c';
}
