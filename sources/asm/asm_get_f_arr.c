/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_f_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 18:05:40 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** get_f_arr() returns an array of poiners to functions:
** w_is_reg(), w_is_dir(), w_is_indir() which is later used by
** check_arg()
**
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
