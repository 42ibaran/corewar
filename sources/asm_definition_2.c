/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_definition_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:16:30 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 13:19:00 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		word_is_indirect(t_word *word)
{
	if (!word->is_command && !word->is_instruction
			&& !word->is_operation && !word->is_register && !word->is_direct)
		word->is_indirect = 1;
}

void		word_is_label(char *line, int j, t_word *word)
{
	if (line[j + word->is_direct] == ':')
		word->is_label = 1;
}

void		word_is_separator(char *line, int j, t_word *word)
{
	if (line[j] == SEPARATOR_CHAR)
		word->is_separator = 1;
}

void		word_is_command(char *line, int j, int i, t_word *word)
{
	if (!ft_strncmp(NAME_CMD_STRING, line + j, i - j + 1))
		word->is_name = 1;
	else if (!ft_strncmp(COMMENT_CMD_STRING, line + j, i - j + 1))
		word->is_comment = 1;
	if (word->is_name || word->is_comment)
		word->is_command = 1;
}

void		word_is_quote(t_word *word, char quote)
{
	if (quote)
		word->is_quote = 1;
}
