/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_definition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:16:30 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/27 14:22:33 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		word_is_space(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)i;
	(void)prev_quote;
	if ((line[j] == ' ' || line[j] == '\t' || line[j] == '\n'))
		word->is_space = 1;
}

void		word_is_instruction(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)j;
	(void)prev_quote;
	if (line[i] == ':')
		word->is_instruction = 1;
}

void		word_is_operation(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	static char		table[16][6] = {
		"live", "ld", "st", "add", "sub", "and", "or", "xor",
		"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};
	int				k;

	(void)prev_quote;
	if (word->is_instruction)
		return ;
	k = -1;
	while (++k < 16)
		if (!ft_strncmp(table[k], line + j, i - j + 1))
			word->is_operation = 1;
}

void		word_is_register(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	int		k;

	(void)prev_quote;
	if (line[j] == 'r' && !word->is_label && !word->is_instruction)
	{
		//ft_printf(">>%s\n", line + j);
		k = i - j;
		word->is_register = 1;
		if (k > 2 || k == 0)
			error(0); // invalid register number
		while (k > 0)
		{
			if ('0' > line[j + k] || line[j + k] > '9')
				error(0); // invalid register number
			k--;
		}
	}
}

void		word_is_direct(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)prev_quote;
	(void)i;
	if (line[j] == '%')
		word->is_direct = 1;
}

void		word_is_indirect(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)line;
	(void)i;
	(void)j;
	(void)prev_quote;
	if (!word->is_command && !word->is_instruction
			&& !word->is_operation && !word->is_register && !word->is_direct)
		word->is_indirect = 1;
}

void		word_is_label(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)prev_quote;
	(void)i;
	if (line[j + word->is_direct] == ':')
		word->is_label = 1;
}

void		word_is_separator(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)i;
	(void)prev_quote;
	if (line[j] == SEPARATOR_CHAR)
		word->is_separator = 1;
}

void		word_is_command(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)prev_quote;
	if (!ft_strncmp(NAME_CMD_STRING, line + j, i - j + 1))
		word->is_name = 1;
	else if (!ft_strncmp(COMMENT_CMD_STRING, line + j, i - j + 1))
		word->is_comment = 1;
	if (word->is_name || word->is_comment)
		word->is_command = 1;
}

void		word_is_quote(char *line, int j, int i,
			t_word *word, char prev_quote)
{
	(void)i;
	(void)j;
	(void)line;
	if (prev_quote)
		word->is_quote = 1;
}
