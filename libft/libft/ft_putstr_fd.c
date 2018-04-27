/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 01:14:03 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/15 09:32:39 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

size_t		ft_putstr_fd(const char *s, int fd, size_t size)
{
	if (!s)
		return (0);
	write(fd, s, size);
	return (size);
}

size_t		ft_wputstr_fd(const wchar_t *s, int fd, size_t size)
{
	size_t i;
	size_t res;

	if (!s)
		return (0);
	res = 0;
	i = 0;
	while (res + count_bytes(s[i]) <= size)
	{
		ft_putchar_fd(s[i], fd);
		res += count_bytes(s[i]);
		i++;
	}
	return (res);
}
