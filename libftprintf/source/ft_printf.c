/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:51:20 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 18:36:46 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fix_conversion(t_special *spec)
{
	if (spec->conversion->ascii == 'D' || spec->conversion->ascii == 'U' ||
			spec->conversion->ascii == 'O')
		spec->size = g_sizes + LONG_INT;
}

static void	print_special(const char **src, va_list *ap)
{
	t_special	special;

	read_flags(src);
	special.width = ft_positive_atoi(src);
	special.precision = read_precision(src);
	special.size = read_size(src);
	special.conversion = read_conversion(src);
	fix_conversion(&special);
	special.conversion->f(&special, ap);
}

int			ft_printf(const char *src, ...)
{
	va_list		ap;

	g_buff.cur = 0;
	g_buff.line = malloc(PRINTF_BUFF_SIZE);
	va_start(ap, src);
	fill_sizes();
	fill_convs();
	fill_flags();
	while (*src)
	{
		if (*src == '%')
		{
			++src;
			print_special(&src, &ap);
			continue;
		}
		pf_write(*src);
		++src;
	}
	va_end(ap);
	pf_write_tail();
	free(g_buff.line);
	return (g_buff.ret * PRINTF_BUFF_SIZE + g_buff.cur);
}

size_t		ft_snprintf(char *line, size_t cur, const char *src, ...)
{
	va_list	ap;

	/* FIXME only 1 filling pls */
	g_buff.line = line;
	g_buff.cur = cur;
	va_start(ap, src);
	fill_sizes();
	fill_convs();
	fill_flags();
	while (*src)
	{
		if (*src == '%')
		{
			++src;
			print_special(&src, &ap);
			continue;
		}
		pf_write(*src);
		++src;
	}
	va_end(ap);
	return (g_buff.cur);
}
