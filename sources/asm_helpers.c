/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:57 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 18:11:57 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

void	error(char code)
{
	if (code == ERR_MEMORY)
		ft_printf("Error: Can't allocate memory\n");
	else if (code == ERR_COMMON)
		ft_printf("Error\n");
	else if (code == ERR_USAGE)
		ft_printf("usage: ./asm filename.s\n");
	else if (code == ERR_READ)
		ft_printf("Error: Can't open source file\n");
	else if (code == ERR_WRITE)
		ft_printf("Error: Can't open/create output file\n");
	else if (code == ERR_MAGIC)
		ft_printf("Error: Invalid magic header\n");
	//f_free();
	exit(EXIT_FAILURE);
}
