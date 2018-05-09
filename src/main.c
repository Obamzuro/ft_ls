/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 01:06:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/05/09 17:37:48 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			main(int argc, char **argv)
{
	int		posafterparams;

	EXITZERO(g_buff.line = malloc(PRINTF_BUFF_SIZE));
	g_buff.cur = 0;
	g_nameapp = argv[0];
	pf_filling_globals();
	posafterparams = fill_params(argc, argv);
	print_files(argc, argv, posafterparams);
	write(1, g_buff.line, g_buff.cur);
	free(g_buff.line);
}
