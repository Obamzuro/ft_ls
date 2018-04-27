/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 01:37:41 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/13 13:11:28 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}

void	ft_putnbr_common(intmax_t n, char base, char top)
{
	ft_putnbr_fd_common(n, 1, base, top);
}

void	ft_uputnbr_common(uintmax_t n, char base, char top)
{
	ft_uputnbr_fd_common(n, 1, base, top);
}
