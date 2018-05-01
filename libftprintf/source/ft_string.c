/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:42:28 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 19:02:57 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		print_nsymb(size_t diff, char symb)
{
	size_t		i;

	i = 0;
	while (i < diff)
	{
		pf_write(symb);
		i++;
	}
}

static size_t	print_str(t_special *spec, char *n, size_t size)
{
	size_t num;

	num = 0;
	if (spec->conversion->ascii == 's')
	{
		pf_putstr(n, size);
		num = size;
	}
	else if (spec->conversion->ascii == 'S')
		num = pf_wputstr((wchar_t *)n);
	return (num);
}

static void		stabilize_width(t_special *spec, char *n)
{
	size_t		nsize;
	size_t		diffwidth;

	diffwidth = 0;
	nsize = 0;
	nsize = spec->conversion->ascii == 's' ? pf_strlen(n)
		: pf_wstrlen((wchar_t *)n);
	if (spec->precision >= 0 && 
			spec->precision < (ssize_t)nsize && spec->conversion->ascii == 's')
		nsize = spec->precision;
	if (spec->width > nsize)
		diffwidth = spec->width - nsize;
	if (!g_flags[minus].exist)
	{
		if (g_flags[zero].exist)
			print_nsymb(diffwidth, '0');
		else
			print_nsymb(diffwidth, ' ');
	}
	nsize = print_str(spec, n, nsize);
	if (g_flags[minus].exist)
		print_nsymb(diffwidth, ' ');
//	*res += spec->width > (int)nsize ? spec->width : nsize;
}

void			print_string(t_special *spec, va_list *ap)
{
	char	*n;
	char	ret;

	n = va_arg(*ap, char*);
	ret = 0;
	if (spec->conversion->ascii == 's' && spec->size->type == LONG_INT)
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
	stabilize_width(spec, n);
	if (ret)
		spec->conversion->ascii = 's';
}
