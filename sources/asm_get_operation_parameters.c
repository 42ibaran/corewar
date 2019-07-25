/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_operation_parameters.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:05:51 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 18:08:39 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_check_oper	get_check_operation(char code)
{
	static t_check_oper	function[16] = {
		&check_args_live, &check_args_ld, &check_args_st,
		&check_args_add, &check_args_sub, &check_args_and,
		&check_args_or, &check_args_xor,&check_args_zjmp,
		&check_args_ldi, &check_args_sti, &check_args_fork,
		&check_args_lld, &check_args_lldi, &check_args_lfork,
		&check_args_aff
	};

	return (function[code - 1]);
}

t_fill_oper		get_fill_operation(char code)
{
	static t_fill_oper	function[16] = {
		&fill_live, &fill_ld, &fill_st,
		&fill_add, &fill_sub, &fill_and,
		&fill_or, &fill_xor,&fill_zjmp,
		&fill_ldi, &fill_sti, &fill_fork,
		&fill_lld, &fill_lldi, &fill_lfork,
		&fill_aff
	};

	return (function[code - 1]);
}

char			get_dir_size(char code)
{
	static char		size[16] = {
		4, 4, 4, 4, 4, 4, 4, 4,
		2, 2, 2, 2,
		4,
		2, 2,
		4
	};

	return (size[code - 1]);
}

char			get_is_type_code_required(char code)
{
	static char		type_req[16] = {
		0,
		1, 1, 1, 1, 1, 1, 1,
		0,
		1, 1,
		0,
		1, 1,
		0,
		1
	};

	return (type_req[code - 1]);
}

char		get_oper_code(char *name)
{
	static char		table[16][6] = {
		"live", "ld", "st", "add", "sub", "and", "or", "xor",
		"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};
	int				i;

	i = -1;
	while (++i < 16)
		if (!ft_strcmp(table[i], name))
			return (i + 1);
	return (-1);
}
