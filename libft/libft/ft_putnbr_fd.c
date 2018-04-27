/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 01:18:01 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/20 18:40:56 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "2147483658", 10);
			return ;
		}
		n = -n;
	}
	if (n > -10 && n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + 48, fd);
	}
}

void		ft_putnbr_fd_common(intmax_t n, int fd, char base, char top)
{
	intmax_t	j;
	intmax_t	dop;
	int			a;
	char		*baseline;

	if (top)
		baseline = "0123456789ABCDEF";
	else
		baseline = "0123456789abcdef";
	j = 1;
	dop = n;
	while (dop / base)
	{
		j *= base;
		dop /= base;
	}
	while (j)
	{
		a = n / j % base;
		a = a > 0 ? baseline[a] : baseline[-a];
		write(fd, &a, 1);
		j /= base;
	}
}

void		ft_uputnbr_fd_common(uintmax_t n, int fd, char base, char top)
{
	uintmax_t	j;
	uintmax_t	dop;
	int			a;
	char		*baseline;

	if (top)
		baseline = "0123456789ABCDEF";
	else
		baseline = "0123456789abcdef";
	j = 1;
	dop = n;
	while (dop / base)
	{
		j *= base;
		dop /= base;
	}
	while (j)
	{
		a = n / j % base;
		a = baseline[a];
		write(fd, &a, 1);
		j /= base;
	}
}
