/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 15:51:20 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/21 18:21:18 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	read_conversion(const char **src, t_conv_corr **conversion)
{
	size_t	i;
	char	error;

	i = 0;
	error = 0;
	if (!**src)
		return (-1);
	while (i < AM_CONVS)
	{
		if (**src == g_convs[i].ascii)
		{
			*conversion = g_convs + i;
			++(*src);
			return (0);
		}
		++i;
	}
	return (-2);
}

void		fix_conversion(t_special *spec)
{
	if (!spec->conversion)
		return ;
	if (spec->conversion->ascii == 'D' || spec->conversion->ascii == 'U' ||
			spec->conversion->ascii == 'O')
		spec->size = g_sizes + LONG_INT;
}

void		print_unknown(t_special *special, int *res, const char *src)
{
	int i;

	i = 0;
	if (!special->width)
	{
		++(*res);
		write(1, src, 1);
		return ;
	}
	if (special->flag[minus].exist)
		write(1, src, 1);
	while (i < special->width - 1)
	{
		if (special->flag[zero].exist)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		i++;
	}
	if (!special->flag[minus].exist)
		write(1, src, 1);
	*res += special->width;
}

static void	print_special(const char **src, va_list *ap, int *res)
{
	t_special	special;
	char		convret;

	if (read_flags(src, special.flag) == -1
	|| read_width(src, &(special.width), ap) == -1
	|| read_precision(src, &(special.precision), ap) == -1
	|| read_size(src, &special.size) == -1)
		return ;
	convret = read_conversion(src, &special.conversion);
	if (convret == -1)
		return ;
	else if (convret == -2)
	{
		print_unknown(&special, res, *src);
		++(*src);
		return ;
	}
	fix_conversion(&special);
	special.conversion ? (special.conversion)->f(&special, ap, res) : 1;
}

int			ft_printf(const char *src, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, src);
	fill_sizes();
	fill_convs();
	fill_convs_plus();
	res = 0;
	while (*src)
	{
		if (*src == '%')
		{
			++src;
			print_special(&src, &ap, &res);
			continue;
		}
		write(1, src, 1);
		++src;
		++res;
	}
	return (res);
}
