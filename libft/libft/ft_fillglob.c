/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillglob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 09:33:28 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/20 18:36:40 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fill_convs(void)
{
	g_convs[0].ascii = 'd';
	g_convs[0].f = print_decimal;
	g_convs[1].ascii = 'i';
	g_convs[1].f = print_decimal;
	g_convs[2].ascii = 'u';
	g_convs[2].f = print_unsigned;
	g_convs[3].ascii = 'D';
	g_convs[3].f = print_decimal;
	g_convs[4].ascii = 'U';
	g_convs[4].f = print_unsigned;
	g_convs[5].ascii = 'o';
	g_convs[5].f = print_unsigned_octal;
	g_convs[6].ascii = 'O';
	g_convs[6].f = print_unsigned_octal;
	g_convs[7].ascii = 'X';
	g_convs[7].f = print_unsigned_hex;
	g_convs[8].ascii = 'x';
	g_convs[8].f = print_unsigned_hex;
}

void	fill_convs_plus(void)
{
	g_convs[9].ascii = 'c';
	g_convs[9].f = print_char;
	g_convs[10].ascii = 'C';
	g_convs[10].f = print_char;
	g_convs[11].ascii = 's';
	g_convs[11].f = print_string;
	g_convs[12].ascii = 'S';
	g_convs[12].f = print_string;
	g_convs[13].ascii = '%';
	g_convs[13].f = print_char;
	g_convs[14].ascii = 'p';
	g_convs[14].f = print_pointer;
	g_convs[14].ascii = 'b';
	g_convs[14].f = print_binary;
}

void	fill_sizes(void)
{
	g_sizes[INTMAX_T].size = INTMAX_T;
	g_sizes[INTMAX_T].spec = "j";
	g_sizes[SIZE_T].size = SIZE_T;
	g_sizes[SIZE_T].spec = "z";
	g_sizes[LONG_LONG_INT].size = LONG_LONG_INT;
	g_sizes[LONG_LONG_INT].spec = "ll";
	g_sizes[LONG_INT].size = LONG_INT;
	g_sizes[LONG_INT].spec = "l";
	g_sizes[SHORT_INT].size = SHORT_INT;
	g_sizes[SHORT_INT].spec = "h";
	g_sizes[CHAR].size = CHAR;
	g_sizes[CHAR].spec = "hh";
	g_sizes[INT].size = INT;
	g_sizes[INT].spec = "";
}

void	fill_flags(t_flags_corr *flag)
{
	flag[minus].flag = minus;
	flag[minus].ascii = '-';
	flag[minus].exist = 0;
	flag[plus].flag = plus;
	flag[plus].ascii = '+';
	flag[plus].exist = 0;
	flag[space].flag = space;
	flag[space].ascii = ' ';
	flag[space].exist = 0;
	flag[sharp].flag = sharp;
	flag[sharp].ascii = '#';
	flag[sharp].exist = 0;
	flag[zero].flag = zero;
	flag[zero].ascii = '0';
	flag[zero].exist = 0;
}
