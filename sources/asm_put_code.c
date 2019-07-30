/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:00:35 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/30 12:42:22 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		put_arg_val_into_binary(t_operation *oper, long long arg_val,
			int i, int j)
{
	int		divider;

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

unsigned int		invert_arg_val(int val, char arg_size)
{
	char	*bin_str;
	char	*bin_str_16;
	int		i;

	bin_str = ft_itoa_base(-val, 2);
	if (!(bin_str_16 = (char*)malloc(sizeof(char) * (8 * arg_size + 1))))
		error(ERR_MEMORY);
	ft_fillstr(bin_str_16, '0', 8 * arg_size);
	ft_strcpy(bin_str_16 + (8 * arg_size - ft_strlen(bin_str)), bin_str);
	i = -1;
	while (++i < 8 * arg_size)
	{
		if (bin_str_16[i] == '0')
			bin_str_16[i] = '1';
		else if (bin_str_16[i] == '1')
			bin_str_16[i] = '0';
	}
	while (--i > -1)
	{
		if (bin_str_16[i] == '0')
		{
			bin_str_16[i] = '1';
			break ;
		}
		else
			bin_str_16[i] = '0';
	}
	val = ft_atoi_base(bin_str_16, 2);
	free(bin_str_16);
	free(bin_str);
	return (val);
}

int		encode_operation(t_operation *oper, t_instruction *instr,
		int i, int j)
{
	long long		arg_val;

	if (oper->arg_type[j] == 0)
		arg_val = ft_atoi(oper->arg_str[j] + 1);
	else if (oper->arg_type[j] == 1)
	{
		if (ft_strisnum(oper->arg_str[j] + 1))
			arg_val = ft_atoi(oper->arg_str[j] + 1);
		else
			arg_val = get_label_distance(oper, instr, oper->arg_str[j] + 2);
	}
	else
	{
		if (ft_strisnum(oper->arg_str[j]))
			arg_val = ft_atoi(oper->arg_str[j]);
		else
			arg_val = get_label_distance(oper, instr, oper->arg_str[j] + 1);
	}
	if (arg_val < 0)
		arg_val = invert_arg_val(arg_val, oper->arg_size[j]);
	return (put_arg_val_into_binary(oper, arg_val, i, j));
}

void		code(t_instruction *instr)
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
	//print_all_instuctions(first_instr);
}
