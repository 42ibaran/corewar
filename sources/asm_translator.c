/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:07:54 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 14:54:00 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		start_translate(t_output **out)
{
	*out = init_output();
	(*out)->instr = NULL;
	(*out)->champ = init_champion();
	g_free.first_out = *out;
}

static char		is_good_to_code(t_output *out, t_word *word)
{
	return (out->champ->name_size != -1 && out->champ->comment_size != -1
		&& !word->is_quote);
}

static void		is_it_an_error(t_word *word, int skip_lines)
{
	if (!word->is_quote)
		lex_error(ERR_NO_NAME_OR_COMMENT, NULL);
	if (skip_lines < 0)
		lex_error(ERR_UNEXPECTED_TOKEN, word->str);
}

/*
** translate() first looks for name and/or comment and then reads the asm code
** P.S. creator is sorry for sending skip_lines as a parameter
*/

t_output		*translate(t_string *string, int skip_lines)
{
	t_output		*out;
	t_word			*word;

	start_translate(&out);
	while (string && (g_input_l = string->nbr))
	{
		if (!(word = string->word))
		{
			string = string->next;
			continue ;
		}
		if (!ft_strcmp(word->str, NAME_CMD_STRING))
			skip_lines = name(out->champ, string);
		else if (!ft_strcmp(word->str, COMMENT_CMD_STRING))
			skip_lines = comment(out->champ, string);
		else if (is_good_to_code(out, word))
		{
			code(out->instr = prepare_operations(string, NULL, NULL));
			break ;
		}
		else
			is_it_an_error(word, --skip_lines);
		string = string->next;
	}
	return (out);
}
