/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_definition_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 16:16:30 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 12:02:48 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		word_is_space(char *line, int j, t_word *word)
{
	if ((line[j] == ' ' || line[j] == '\t' || line[j] == '\n'))
		word->is_space = 1;
}

void		word_is_instruction(char *line, int i, t_word *word)
{
	if (line[i] == ':')
		word->is_instruction = 1;
}

void		word_is_operation(char *line, int j, int i, t_word *word)
{
	int				k;
	static char		table[16][6] = {
		"live", "ld", "st", "add", "sub", "and", "or", "xor",
		"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"
	};

	if (word->is_instruction)
		return ;
	k = -1;
	while (++k < 16)
		if (!ft_strncmp(table[k], line + j, i - j + 1))
			word->is_operation = 1;
}

void		word_is_register(char *line, int j, int i, t_word *word)
{
	int		k;

	if (line[j] == 'r' && !word->is_label && !word->is_instruction)
	{
		k = i - j;
		word->is_register = 1;
		if (k > 2 || k == 0)
			lex_error(ERR_INV_REGISTER, NULL);
		while (k > 0)
		{
			if ('0' > line[j + k] || line[j + k] > '9')
				lex_error(ERR_INV_REGISTER, NULL);
			k--;
		}
	}
}

void		word_is_direct(char *line, int j, t_word *word)
{
	if (line[j] == '%')
		word->is_direct = 1;
}
