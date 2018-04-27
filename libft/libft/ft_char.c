/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:07:42 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 08:51:59 by obamzuro         ###   ########.fr       */
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

static void	stabilize_width(t_special *spec, uintmax_t n, int *res)
{
	ssize_t		nsize;
	size_t		diffwidth;

	diffwidth = 0;
	nsize = 1;
	if (spec->width > nsize)
		diffwidth = spec->width - nsize;
	if (!spec->flag[minus].exist && spec->flag[zero].exist)
		print_nsymb(diffwidth, '0');
	else if (!spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	if (spec->conversion->ascii == 'C')
		nsize = ft_putchar(n);
	else
		write(1, &n, 1);
	if (spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	*res += spec->width > nsize ? spec->width : nsize;
}

void		print_char(t_special *spec, va_list *ap, int *res)
{
	uintmax_t	n;
	char		ret;

	ret = 0;
	if (spec->conversion->ascii == 'c' && spec->size->size == LONG_INT)
	{
		ret = 1;
		spec->conversion->ascii = 'C';
	}
	if (spec->conversion->ascii == '%')
		n = '%';
	else
		n = va_arg(*ap, unsigned int);
	stabilize_width(spec, n, res);
	if (ret)
		spec->conversion->ascii = 'c';
}
