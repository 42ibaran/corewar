/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:28:02 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 12:45:05 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	new_output->champ = NULL;
	new_output->instr = NULL;
	return (new_output);
}
