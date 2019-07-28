/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:41:28 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:48 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	t_string	*string;
	t_output	*output;

	g_input_line = 0;
	string = read_and_save(ac, av);
	output = translate(string);
	write_into_file(output, av[ac - 1]);
	return (0);
}
