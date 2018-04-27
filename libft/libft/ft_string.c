/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:42:28 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 08:56:16 by obamzuro         ###   ########.fr       */
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

static size_t	print_str(t_special *spec, char *n, size_t size)
{
	size_t i;

	i = 0;
	if (spec->conversion->ascii == 's')
		i = ft_putstr(n, size);
	else if (spec->conversion->ascii == 'S')
		i = ft_wputstr((wchar_t *)n, size);
	return (i);
}

static void		stabilize_width(t_special *spec, char *n, int *res)
{
	size_t		nsize;
	size_t		diffwidth;
	size_t		total;

	diffwidth = 0;
	nsize = 0;
	total = 0;
	nsize = spec->conversion->ascii == 's' ? ft_strlen(n)
		: ft_wstrlen((wchar_t *)n);
	total = spec->conversion->ascii == 's' ?
		nsize : ft_wstrlen_total((wchar_t *)n);
	if (spec->precision != -1 && (size_t)spec->precision < total)
		total = spec->precision;
	if (spec->conversion->ascii == 'S' && spec->width > (int)total)
		diffwidth = spec->width - total;
	if (spec->conversion->ascii == 's' && spec->width > (int)total)
		diffwidth = spec->width - total;
	if (!spec->flag[minus].exist && spec->flag[zero].exist)
		print_nsymb(diffwidth, '0');
	else if (!spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	nsize = print_str(spec, n, total);
	if (spec->flag[minus].exist)
		print_nsymb(diffwidth, ' ');
	*res += spec->width > (int)nsize ? spec->width : nsize;
}

void			print_string(t_special *spec, va_list *ap, int *res)
{
	char	*n;
	char	ret;

	n = va_arg(*ap, char*);
	ret = 0;
	if (spec->conversion->ascii == 's' && spec->size->size == LONG_INT)
	{
		spec->conversion->ascii = 'S';
		ret = 1;
	}
	if (!n)
	{
		if (spec->conversion->ascii == 's')
			n = "(null)";
		else if (spec->conversion->ascii == 'S')
			n = (char *)L"(null)";
	}
	stabilize_width(spec, n, res);
	if (ret)
		spec->conversion->ascii = 's';
}
