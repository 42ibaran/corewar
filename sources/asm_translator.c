/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:07:54 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:40 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_output	*translate(t_string *string)
{
	t_output	*out;
	t_champion	*champ;
	t_instruction *instr;
	t_word		*word;

	champ = init_champion();
	out = init_output();
	while (string)
	{
		g_input_line = string->nbr;
		word = string->word;
		//
		if (!word)
		{
			string = string->next;
			continue ;
		}
		//
		if (!ft_strcmp(word->str, NAME_CMD_STRING)) // protect from duplicates
			name(champ, string);
		else if (!ft_strcmp(word->str, COMMENT_CMD_STRING)) // protect from duplicates
			comment(champ, string);
		else if (champ->name_size != -1 && champ->comment_size != -1)
		{
			instr = prepare_operations(string, NULL, NULL);
			code(instr);
			out->champ = champ;
			out->instr = instr;
			break ;
		}
		else// if (word && !word->is_quote)
			lex_error(ERR_NO_NAME_OR_COMMENT, NULL);
		string = string->next;
	}
	g_input_line = 0;
	// ft_printf("%s\n", champ->name);
	// ft_printf("%s\n", champ->comment);
	return (out);
}
