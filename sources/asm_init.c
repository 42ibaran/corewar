/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:28:02 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 18:21:12 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

t_string		*init_string(int nbr)
{
	t_string	*new_string;

	if (!(new_string = (t_string*)malloc(sizeof(t_string))))
		error(ERR_MEMORY);
	new_string->line = NULL;
	new_string->nbr = nbr;
	new_string->word = NULL;
	new_string->last_word = NULL;
	new_string->next = NULL;
	return (new_string);
}

t_word			*init_word(char *line, int j, int i)
{
	t_word		*word;
	
	if (!(word = (t_word*)malloc(sizeof(t_word))))
		error(ERR_MEMORY);
	if (!(word->str = ft_strndup(line + j, i - j + 1)))
		error(ERR_MEMORY);
	word->is_instruction = 0;
	word->is_operation = 0;
	word->is_register = 0;
	word->is_direct = 0;
	word->is_indirect = 0;
	word->is_label = 0;
	word->is_separator = 0;
	word->is_command = 0;
	word->is_name = 0;
	word->is_comment = 0;
	word->is_space = 0;
	word->is_quote = 0;
	word->next = NULL;
	return (word);
}

t_output		*init_output(void)
{
	t_output	*new_output;

	if (!(new_output = (t_output*)malloc(sizeof(t_output))))
		error(ERR_MEMORY);
	if (!(new_output->string = ft_strnew(BUFF_OUT_STR - 1)))
		error(ERR_MEMORY);
	new_output->pos = 0;
	new_output->size = BUFF_OUT_STR;
	return (new_output);
}

t_champion		*init_champion(void)
{
	t_champion	*new_champion;

	if (!(new_champion = (t_champion*)malloc(sizeof(t_champion))))
		error(ERR_MEMORY);
	new_champion->name[0] = '\0';
	new_champion->name_size = -1;
	new_champion->comment[0] = '\0';
	new_champion->comment_size = -1;
	new_champion->code = NULL;
	new_champion->code_size = -1;
	return (new_champion);
}

t_instruction	*init_instruction(char *name)
{
	t_instruction	*new_instruction;

	if (!(new_instruction = (t_instruction*)malloc(sizeof(t_instruction))))
		error(ERR_MEMORY);
	new_instruction->name= name;
	new_instruction->length = -1;
	new_instruction->operation = NULL;
	new_instruction->last_operation = NULL;
	new_instruction->next = NULL;
	return (new_instruction);
}

t_operation		*init_operation(char *name)
{
	t_operation	*new_operation;

	if (!(new_operation = (t_operation*)malloc(sizeof(t_operation))))
		error(ERR_MEMORY);
	new_operation->oper_code = get_oper_code(name);
	new_operation->arg_type_code = -1;
	new_operation->arg_value[0] = 0;
	new_operation->arg_value[1] = 0;
	new_operation->arg_value[2] = 0;
	new_operation->arg_str[0] = NULL;
	new_operation->arg_str[1] = NULL;
	new_operation->arg_str[2] = NULL;
	new_operation->arg_type[0] = -1;
	new_operation->arg_type[1] = -1;
	new_operation->arg_type[2] = -1;
	new_operation->length = -1;
	new_operation->binary = NULL;
	new_operation->next = NULL;
	return (new_operation);
}
