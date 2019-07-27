/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:00:35 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/27 15:23:46 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

unsigned char	calculate_arg_type_code(t_operation *oper)
{
	int				i;
	char			arg_type_code = 0b0;

	i = -1;
	while (++i < 3)
	{
		if (oper->arg_type[i] == 0)
			arg_type_code += 0b01;
		else if (oper->arg_type[i] == 1)
			arg_type_code += 0b10;
		else if (oper->arg_type[i] == 2)
			arg_type_code += 0b11;
		arg_type_code *= 0b100;
	}
	return (arg_type_code);
}

void		fill_arg_type(t_operation *oper, t_word *word, char arg_nbr)
{
	char	type;

	type = -1;
	if (word->is_register)
	{
		oper->arg_type[(int)arg_nbr] = 0;
		oper->arg_size[(int)arg_nbr] = 1;
	}
	else if (word->is_direct)
	{
		oper->arg_type[(int)arg_nbr] = 1;
		oper->arg_size[(int)arg_nbr] = get_dir_size(oper->oper_code);
	}
	else if (word->is_indirect)
	{
		oper->arg_type[(int)arg_nbr] = 2;
		oper->arg_size[(int)arg_nbr] = 2;
	}
}

/*
** this function checks operation arguments,
** calculate length of opertion's code,
** allocate memory for it and calculate arg_type_code
*/
void		fill_operation(t_operation *oper, t_word *word)
{
	t_check_oper	checking_fun;
	int				i;

	checking_fun = get_check_operation(oper->oper_code);
	checking_fun(oper, word);
	oper->length = 1;
	i = -1;
	while (++i < 3)
		oper->length += oper->arg_size[i];
	if (get_is_type_code_required(oper->oper_code))
	{
		oper->length += 1;
		oper->arg_type_code = calculate_arg_type_code(oper);
	}
	if (!(oper->binary =
			(unsigned char*)malloc(sizeof(unsigned char) * oper->length)))
		error(ERR_MEMORY);
}

t_instruction	*prepare_operations(t_string *string, t_instruction *instr,
				t_instruction *next_instr)
{
	t_word			*word;
	
	if (!string)
	{
		return (instr);
	}
	word = string->word;
	if (word && word->is_instruction)
	{
		new_instruction(&instr, &next_instr, word->str);
		if (word)
			word = word->next;
	}
	if (word && word->is_operation)
	{
		new_operation(&instr, &next_instr, word->str);
		fill_operation(next_instr->last_operation, word);
		next_instr->length += (next_instr->length == -1 ? 1 : 0);
		next_instr->length += next_instr->last_operation->length;
	}
	return (prepare_operations(string->next, instr, next_instr));
}

int		put_arg_val_into_binary(t_operation *oper, unsigned int arg_val,
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

int		invert_arg_val(int val, char arg_size)
{
	char	*bin_str;
	char	*bin_str_16;
	int		i;

	bin_str = ft_itoa_base(-val, 2);
	if (!(bin_str_16 = (char*)malloc(sizeof(char) * 8 * arg_size)))
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
	return (val);
}

/*
** rewpair of negative arg_vals needed 
*/
int		encode_operation(t_operation *oper, t_instruction *instr,
		int i, int j)
{
	int		arg_val;

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
