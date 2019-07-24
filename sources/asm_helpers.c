/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:57 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 12:59:20 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

void	error(char code)
{
	if (code == ERR_MEMORY)
		ft_printf("Memory allocation error\n");
	else if (code == ERR_COMMON)
		ft_printf("Error\n");
	else if (code == ERR_USAGE)
		ft_printf("usage: ./asm filename.s\n");
	else if (code == ERR_FILE)
		ft_printf("Cannot open file\n");
	//f_free();
	exit(EXIT_FAILURE);
}
