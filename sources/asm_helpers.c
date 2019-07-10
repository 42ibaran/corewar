/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:57 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/10 15:58:06 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error(char code)
{
	if (code == 0)
		ft_printf("Error\n");
	if (code == -1)
		ft_printf("usage: ./asm filename.s\n");
	if (code == -2)
		ft_printf("Cannot open file\n");
	//f_free();
	exit(EXIT_FAILURE);
}
