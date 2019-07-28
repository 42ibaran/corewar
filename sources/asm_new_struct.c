/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_new_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 12:57:17 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 16:15:07 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_globals(void)
{
	g_input_line = 0;
	g_free.first_champion = NULL;
	g_free.first_instr = NULL;
	g_free.first_string = NULL;
	g_free.first_out = NULL;
}

void	new_string(t_string **string, t_string **next_string, int nbr)
{
	if (!*string)
	{
		*string = init_string(nbr);
		*next_string = *string;
		g_free.first_string = *string;
	}
	else
	{
		(*next_string)->next = init_string(nbr);
		(*next_string) = (*next_string)->next;
	}
}

void	new_instruction(t_instruction **instr, t_instruction **next_instr,
		char *str)
{
	if (!*instr)
	{
		*instr = init_instruction(str);
		*next_instr = *instr;
		g_free.first_instr = *instr;
	}
	else
	{
		if (!(*instr)->next && !(*instr)->name)
			(*instr)->name = str;
		else
		{
			(*next_instr)->next = init_instruction(str);
			(*next_instr) = (*next_instr)->next;
		}
	}
}

void	new_operation(t_instruction **instr, t_instruction **next_instr,
		char *str)
{
	if (!*instr)
		new_instruction(instr, next_instr, NULL);
	if (!(*next_instr)->operation)
	{
		(*next_instr)->operation = init_operation(str);
		(*next_instr)->last_operation = (*next_instr)->operation;
	}
	else
	{
		(*next_instr)->last_operation->next = init_operation(str);
		(*next_instr)->last_operation = (*next_instr)->last_operation->next;
	}
}
