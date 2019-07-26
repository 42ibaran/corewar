/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:00:35 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/26 12:49:23 by ibaran           ###   ########.fr       */
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
		type = 0;
		oper->arg_size[(int)arg_nbr] = 1;
	}
	else if (word->is_direct)
	{
		type = 1;
		oper->arg_size[(int)arg_nbr] = get_dir_size(oper->oper_code);
	}
	else if (word->is_indirect)
	{
		type = 2;
		oper->arg_size[(int)arg_nbr] = 2;
	}
	oper->arg_type[(int)arg_nbr] = type;
}

/*
** this function checks operation arguments,
** calculate length of opertion's code,
** allocate memory for it and calculate arg_type_code
*/
void		fill_operation(t_operation *oper, t_word *word)
{
	t_check_oper	checking_fun;
	t_fill_oper		filling_fun;
	int				i;

	checking_fun = get_check_operation(oper->oper_code);
	filling_fun = get_fill_operation(oper->oper_code);
	checking_fun(oper, word);
	oper->length = 1;
	i = -1;
	while (++i < 3)
	{
		oper->length += oper->arg_size[i];
	}
	if (get_is_type_code_required(oper->oper_code))
	{
		oper->length += 1;
		oper->arg_type_code = calculate_arg_type_code(oper);
	}
	if (!(oper->binary = (unsigned char*)malloc(sizeof(unsigned char) * oper->length)))
		error(ERR_MEMORY);
}

void	new_instruction(t_instruction **instr, t_instruction **next_instr,
		char *str)
{
	if (!*instr)
	{
		*instr = init_instruction(str);
		*next_instr = *instr;
	}
	else
	{
		if (!(*instr)->next && !(*instr)->name)
			(*instr)->name = str;
		else
		{
			(*next_instr)->next = init_instruction(str);
			(*next_instr) = (*next_instr)->next;
		}
	}
}

void	new_operation(t_instruction **instr, t_instruction **next_instr,
		char *str)
{
	if (!*instr)
		new_instruction(instr, next_instr, NULL);
	if (!(*next_instr)->operation)
	{
		(*next_instr)->operation = init_operation(str);
		(*next_instr)->last_operation = (*next_instr)->operation;
	}
	else
	{
		(*next_instr)->last_operation->next = init_operation(str);
		(*next_instr)->last_operation = (*next_instr)->last_operation->next;
	}
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

int		put_arg_val_into_binary(t_operation *oper, int arg_val,
			int i, int j)
{
	int		divider;

	divider = ft_power(0x100, oper->arg_size[j] - 1);
	ft_printf("%#x %d\n", divider, oper->arg_size[j]);
	while (divider)
	{
		oper->binary[i] = arg_val / divider;
		arg_val %= 0x100;
		divider /= 0x100;
		i++;
	}
	return (i);
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
		{
			arg_val = ft_atoi(oper->arg_str[j] + 1);
		}
		else
			arg_val = get_label_distance(oper, instr, oper->arg_str[j] + 2);
	}
	else
	{
		if (ft_strisnum(oper->arg_str[j]))
		{
			arg_val = ft_atoi(oper->arg_str[j]);
		}
		else
			arg_val = get_label_distance(oper, instr, oper->arg_str[j] + 1);
	}
	ft_printf("%d ", arg_val);
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
			if (oper->arg_type_code != -1)
			{
				oper->binary[1] = oper->arg_type_code;
				i++;
			}
			while (oper->arg_type[++j] != -1 && j < 3)
			{
				i = encode_operation(oper, first_instr, i, j);
			}
			oper = oper->next;
		}
		instr = instr->next;
	}
	print_all_instuctions(first_instr);
}
