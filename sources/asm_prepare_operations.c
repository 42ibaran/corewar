/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_prepare_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 12:07:42 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 15:07:51 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	calculate_arg_type_code(t_operation *oper)
{
	int				i;
	char			arg_type_code;

	arg_type_code = 0b0;
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

void					fill_arg_type(t_operation *oper, t_word *word,
						char arg_nbr)
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
** fill_operation() checks operation arguments,
** calculate length of opertion's code,
** allocate memory for it and calculate arg_type_code
*/

static void				fill_operation(t_operation *oper, t_word *word,
						int line_nbr)
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
	oper->line_nbr = line_nbr;
	if (!(oper->binary =
			(unsigned char*)malloc(sizeof(unsigned char) * oper->length)))
		error(ERR_MEMORY);
}

t_instruction			*prepare_operations(t_string *string,
						t_instruction *instr, t_instruction *next_instr)
{
	t_word			*word;

	if (!string)
		return (instr);
	g_input_l = string->nbr;
	word = string->word;
	if (word && word->is_instruction)
	{
		new_instruction(&instr, &next_instr, word->str);
		word = word->next;
	}
	if (word)
	{
		new_operation(&instr, &next_instr, word->str);
		fill_operation(next_instr->last_operation, word, string->nbr);
		next_instr->length += (next_instr->length == -1 ? 1 : 0);
		next_instr->length += next_instr->last_operation->length;
	}
	return (prepare_operations(string->next, instr, next_instr));
}
