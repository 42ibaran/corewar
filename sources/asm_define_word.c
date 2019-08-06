/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_define_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 16:23:51 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 14:57:27 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** define() uses functions word_is_*** trying to give a word a definition
*/

static t_word		*define(char *line, int j, int i, char quote)
{
	t_word		*word;

	word = init_word(line, j, i);
	word_is_space(line, j, word);
	word_is_quote(word, quote);
	word_is_separator(line, j, word);
	if (!word->is_space && !word->is_quote && !word->is_separator)
	{
		word_is_command(line, j, i, word);
		word_is_instruction(line, i, word);
		word_is_operation(line, j, i, word);
		word_is_label(line, j, word);
		word_is_register(line, j, i, word);
		word_is_direct(line, j, word);
		word_is_indirect(word);
	}
	return (word);
}

static char		word_is_something(t_word *word)
{
	return (word->is_command || word->is_instruction || word->is_operation
		|| word->is_label || word->is_register || word->is_direct
		|| word->is_indirect || word->is_quote || word->is_separator);
}

t_word			*allocate_and_define(char *line, int i, int j, char quote)
{
	t_word		*word;

	if (!quote && j < i)
		return (NULL);
	word = define(line, i, j, quote);
	if (word_is_something(word))
	{
		if (i != j && quote)
		{
			if (line[j + 1] == '\"')
				word->quote_is_open = 0;
			else
				word->quote_is_open = 1;
		}
		return (word);
	}
	else
	{
		free(word->str);
		free(word);
		return (NULL);
	}
}
