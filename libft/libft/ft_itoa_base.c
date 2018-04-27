/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 22:50:27 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/13 00:08:36 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_it(char *a, intmax_t n, size_t len, char base)
{
	size_t	r;
	char	*baseline;
	int		res;

	baseline = "0123456789ABCDEF";
	a[len] = 0;
	r = 0;
	while (len - r)
	{
		res = n % base;
		res = res > 0 ? res : -res;
		a[len - ++r] = baseline[res];
		n /= base;
	}
}

char		*ft_itoa_base(intmax_t n, char base)
{
	char	*a;
	size_t	r;
	size_t	b;

	b = n;
	r = 1;
	while (n / base)
	{
		++r;
		n /= base;
	}
	a = (char *)malloc(sizeof(char) * (r + 1));
	if (!a)
		return (NULL);
	fill_it(a, b, r, base);
	return (a);
}

void		print_ft_itoa_base(intmax_t n, char base)
{
	char		*a;
	size_t		r;
	intmax_t	b;

	b = n;
	r = 1;
	while (n / base)
	{
		++r;
		n /= base;
	}
	a = (char *)malloc(sizeof(char) * (r + 1));
	if (!a)
		return ;
	fill_it(a, b, r, base);
	write(0, a, r);
	free(a);
}
