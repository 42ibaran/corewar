/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:07:54 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/29 17:02:13 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_output	*translate(t_string *string)
{
	t_output	*out;
	t_champion	*champ;
	t_instruction *instr = NULL;
	t_word		*word;

	champ = init_champion();
	g_free.first_champion = champ;
	out = init_output();
	g_free.first_out = out;
	out->champ = champ;
	while (string)
	{
		g_input_l = string->nbr;
		word = string->word;
		if (!word)
		{
			string = string->next;
			continue ;
		}
		if (!ft_strcmp(word->str, NAME_CMD_STRING))
			name(champ, string);
		else if (!ft_strcmp(word->str, COMMENT_CMD_STRING))
			comment(champ, string);
		else if (champ->name_size != -1 && champ->comment_size != -1
				&& !word->is_quote)
		{
			instr = prepare_operations(string, NULL, NULL);
			code(instr);
			out->instr = instr;
			break ;
		}
		else if (!word->is_quote)
			lex_error(ERR_NO_NAME_OR_COMMENT, NULL);
		string = string->next;
	}
	return (out);
}
