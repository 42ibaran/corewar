/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations_7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 14:55:29 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** code meaning:
** 0 = NULL
** 1 = register
** 2 = direct
** 3 = indirect
** XXX = code
*/

t_check_arg		*get_f_arr(int code)
{
	t_check_arg		*f_arr;
	int				divider;
	int				i;

	if (!(f_arr = (t_check_arg*)malloc(sizeof(t_check_arg) * 4)))
		error(ERR_MEMORY);
	divider = 100;
	i = 0;
	while (divider)
	{
		if (code / divider == 1)
			f_arr[i] = &w_is_reg;
		else if (code / divider == 2)
			f_arr[i] = &w_is_dir;
		else if (code / divider == 3)
			f_arr[i] = &w_is_indir;
		else
			f_arr[i] = NULL;
		code %= divider;
		divider /= 10;
		i++;
	}
	f_arr[i] = NULL;
	return (f_arr);
}
