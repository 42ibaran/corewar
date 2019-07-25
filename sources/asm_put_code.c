/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 12:00:35 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 19:38:27 by ibaran           ###   ########.fr       */
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
		if (oper->arg_type[i] == 0)
			oper->length += 1;
		else if (oper->arg_type[i] == 1)
			oper->length += get_dir_size(oper->oper_code);
		else if (oper->arg_type[i] == 2)
			oper->length += 2;
	}
	if (get_is_type_code_required(oper->oper_code))
	{
		oper->length += 1;
		oper->arg_type_code = calculate_arg_type_code(oper);
	}
	if (!(oper->binary = (char*)malloc(sizeof(char) * oper->length)))
		error(ERR_MEMORY);
}

void		fill_arg_type(t_operation *oper, t_word *word, char arg_nbr)
{
	char	type;

	type = -1;
	if (word->is_register)
		type = 0;
	else if (word->is_direct)
		type = 1;
	else if (word->is_indirect)
		type = 2;
	oper->arg_type[(int)arg_nbr] = type;
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
		(*next_instr)->next = init_instruction(str);
		(*next_instr) = (*next_instr)->next;
	}
}

void	new_operation(t_instruction *instr, char *str)
{
	if (!instr->operation)
	{
		instr->operation = init_operation(str);
		instr->last_operation = instr->operation;
	}
	else
	{
		instr->last_operation->next = init_operation(str);
		instr->last_operation = instr->last_operation->next;
	}
}

void		code(t_champion *champ, t_string *string, t_instruction *instr,
			t_instruction *next_instr)
{
	champ = NULL; //LOOK HERE!!!!

	t_word			*word;
	
	if (!string)
	{
		print_all_instuctions(instr);
		return ;
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
		new_operation(next_instr, word->str);
		fill_operation(next_instr->last_operation, word);
		next_instr->length += (next_instr->length == -1 ? 1 : 0);
		next_instr->length += next_instr->last_operation->length;
	}
	code(champ, string->next, instr, next_instr);
}
