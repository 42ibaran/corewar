/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:41:28 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/27 13:33:23 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

int		main(int ac, char **av)
{
	t_string	*string;
	t_output	*output;

	string = read_and_save(ac, av);
	output = translate(string);
	write_into_file(output, av[ac - 1]);
	return (0);
}
