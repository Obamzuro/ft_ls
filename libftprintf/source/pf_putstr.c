/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:23:41 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 18:36:28 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	count_bytes(int a)
{
	if (a <= 0x7F)
		return (1);
	if (a <= 0x7FF)
		return (2);
	if (a <= 0xFFFF)
		return (3);
	return (4);
}

void		pf_putstr(const char *s, size_t size)
{
	size_t i;

	if (!s)
		return ;
	i = 0;
	while (*s && i < size)
	{
		pf_write(*s);
		++s;
		++i;
	}
}

size_t		pf_wputstr(const wchar_t *s)
{
	size_t res;

	if (!s)
		return (0);
	res = 0;
	while (*s)
	{
		pf_putchar(*s);
		res += count_bytes(*s);
		++s;
	}
	return (res);
}
