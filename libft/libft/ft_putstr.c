/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 01:39:31 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/14 15:03:37 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putstr(const char *s, size_t size)
{
	if (!s)
		return (0);
	return (ft_putstr_fd(s, 1, size));
}

size_t	ft_wputstr(const wchar_t *s, size_t size)
{
	if (!s)
		return (0);
	return (ft_wputstr_fd(s, 1, size));
}
