/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 15:56:48 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 16:16:27 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	f_free_instructions(t_instruction *instr)
{
	t_operation		*oper;
	void			*next;

	while (instr)
	{
		oper = instr->operation;
		while (oper)
		{
			next = oper->next;
			free(oper->binary);
			free(oper);
			oper = next;
		}
		next = instr->next;
		free(instr);
		instr = next;
	}
}

void	f_free_strings(t_string *string)
{
	t_word			*word;
	void			*next;

	while (string)
	{
		word = string->word;
		while (word)
		{
			next = word->next;
			free(word->str);
			free(word);
			word = next;
		}
		next = string->next;
		free(string->line);
		free(string);
		string = next;
	}
}

void	f_free(void)
{
	if (g_free.first_champion)
		free(g_free.first_champion);
	if (g_free.first_instr)
		f_free_instructions(g_free.first_instr);
	if (g_free.first_string)
		f_free_strings(g_free.first_string);
	if (g_free.first_out)
		free(g_free.first_out);
}
