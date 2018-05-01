/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:21:22 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/01 13:21:22 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_write(char src)
{
	if (g_buff.cur >= PRINTF_BUFF_SIZE)
	{
		write(1, g_buff.line, PRINTF_BUFF_SIZE);
		g_buff.cur = 0;
		++g_buff.ret;
	}
	g_buff.line[g_buff.cur] = src;
	++(g_buff.cur);
}

void		pf_write_tail(void)
{
	write(1, g_buff.line, g_buff.cur);
}
