/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_plus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 09:40:43 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/21 18:55:16 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	read_flags(const char **src, t_flags_corr *flag)
{
	size_t i;

	fill_flags(flag);
	while (1)
	{
		if (!**src)
			return (-1);
		i = -1;
		while (++i < AM_FLAGS)
			if (flag[i].ascii == **src)
			{
				flag[i].exist = 1;
				break ;
			}
		if (i == AM_FLAGS)
			break ;
		++(*src);
	}
	return (0);
}

int		ft_atoi_pf(const char **src, char *error)
{
	long int	t;

	error = 0;
	if (!**src)
	{
		*error = -1;
		return (-1);
	}
	if (**src < '0' || **src > '9')
		return (0);
	t = **src - '0';
	while ((*++(*src) && **src >= '0') && **src <= '9' && t >= 0)
		t = t * 10 + (**src - 48);
	if (!**src)
	{
		*error = -1;
		return (-1);
	}
	return (t);
}

char	read_width(const char **src, int *width, va_list *ap)
{
	char error;

	if (**src == '*')
	{
		*width = va_arg(*ap, unsigned int);
		++(*src);
		return (0);
	}
	*width = ft_atoi_pf(src, &error);
	return (error);
}

char	read_precision(const char **src, ssize_t *precision, va_list *ap)
{
	char error;

	error = 0;
	if (!**src)
		error = -1;
	if (**src == '.')
	{
		++(*src);
		if (**src == '*')
		{
			*precision = va_arg(*ap, unsigned int);
			++(*src);
			return (0);
		}
		*precision = ft_atoi_pf(src, &error);
	}
	else
		*precision = -1;
	return (error);
}

char	read_size(const char **src, t_size_corr **size)
{
	size_t	i;
	char	error;

	i = 0;
	error = 0;
	if (!**src)
		return (-1);
	while (i < AM_SIZES)
	{
		if (ft_strnstr(*src, g_sizes[i].spec, ft_strlen(g_sizes[i].spec)))
		{
			*size = g_sizes + i;
			*src += ft_strlen(g_sizes[i].spec);
			return (0);
		}
		++i;
	}
	*size = g_sizes + INT;
	return (0);
}
