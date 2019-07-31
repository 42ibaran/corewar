/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:00:35 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/31 16:27:07 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		put_arg_val_into_binary(t_operation *oper, unsigned int arg_val,
			int i, int j)
{
	unsigned int		divider;

	divider = ft_power(0x100, oper->arg_size[j] - 1);
	while (divider)
	{
		oper->binary[i] = (unsigned char)(arg_val / divider);
		arg_val %= divider;
		divider /= 0x100;
		i++;
	}
	return (i);
}

static int		encode_operation(t_operation *oper, t_instruction *instr,
		int i, int j)
{
	__int128_t		arg_val = 0;
	char			numcheck;
	int				atoi_shift;

	atoi_shift = (oper->arg_type[j] == 2 ? 0 : 1);
	if (oper->arg_type[j] == 0 || (numcheck = ft_strisnum(oper->arg_str[j]
			+ atoi_shift)) == 1)
		arg_val = ft_atoint128(oper->arg_str[j] + atoi_shift);
	else if (numcheck == -1)
		arg_val = ((oper->arg_str[j][atoi_shift] == '-') ? 0x0 : 0xffffffff);
	else if (oper->arg_str[j][atoi_shift] == ':')
		arg_val =
			get_label_distance(oper, instr, oper->arg_str[j] + 1 + atoi_shift);
	else
		lex_error(ERR_INVALID_ARG, oper->arg_str[j]);
	if (arg_val > 0 && arg_val > MAX_ARG_VAL_ABS)
		arg_val = 0xffffffff;
	else if (arg_val < 0 && -arg_val > MAX_ARG_VAL_ABS)
		arg_val = 0x0;
	else if (arg_val < 0)
		arg_val = process_negative_val(arg_val, oper->arg_size[j]);
	return (put_arg_val_into_binary(oper, arg_val, i, j));
}

void			code(t_instruction *instr)
{
	t_operation		*oper;
	t_instruction	*first_instr = instr;
	int				i; // binary string index
	int				j; // argument index

	while (instr)
	{
		oper = instr->operation;
		while (oper)
		{
			g_input_l = oper->line_nbr;
			i = 1;
			j = -1;
			oper->binary[0] = oper->oper_code;
			if (oper->arg_type_code != -1 && ++i)
				oper->binary[1] = oper->arg_type_code;
			while (oper->arg_type[++j] != -1 && j < 3)
				i = encode_operation(oper, first_instr, i, j);
			oper = oper->next;
		}
		instr = instr->next;
	}
}
