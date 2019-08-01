/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_label_distance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 11:31:27 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 12:42:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				instruction_first(t_operation *oper, t_instruction *instr)
{
	t_operation		*tmp;
	int				dist;

	dist = 0;
	tmp = instr->operation;
	while (tmp != oper)
	{
		if (!tmp)
		{
			instr = instr->next;
			tmp = instr->operation;
			continue ;
		}
		dist += tmp->length;
		tmp = tmp->next;
	}
	return (-dist);
}

int				operation_first(t_operation *oper, t_instruction *instr,
				t_instruction *prev_instr)
{
	int				dist;

	dist = 0;
	while (prev_instr != instr)
	{
		if (!oper)
		{
			prev_instr = prev_instr->next;
			oper = prev_instr->operation;
		}
		else
		{
			dist += oper->length;
			oper = oper->next;
		}
	}
	return (dist);
}

t_instruction	*get_instr(t_instruction *first, char *name)
{
	while (first)
	{
		if (first->name && !ft_strncmp(first->name, name, ft_strlen(name))
				&& !ft_strncmp(first->name, name, ft_strlen(first->name) - 1))
			return (first);
		first = first->next;
	}
	return (first);
}

int				get_prev_instr(t_instruction *first, t_operation *oper,
				t_instruction *found, t_instruction **prev_instr)
{
	t_operation		*inner_oper;
	int				label_or_oper;

	label_or_oper = 0;
	while (first)
	{
		inner_oper = first->operation;
		if (first == found)
			label_or_oper = 1;
		while (inner_oper)
		{
			if (inner_oper == oper)
			{
				*prev_instr = first;
				return (label_or_oper == 0 ? 2 : label_or_oper);
			}
			inner_oper = inner_oper->next;
		}
		first = first->next;
	}
	return (-1);
}

int				get_label_distance(t_operation *oper, t_instruction *instr,
				char *name)
{
	char			label_or_oper;
	t_instruction	*found_instr;
	t_instruction	*prev_instr;

	found_instr = get_instr(instr, name);
	label_or_oper = get_prev_instr(instr, oper, found_instr, &prev_instr);
	if (!found_instr)
		lex_error(ERR_UNKNOWN_LABEL, name);
	if (label_or_oper == 1)
		return (instruction_first(oper, found_instr));
	else
		return (operation_first(oper, found_instr, prev_instr));
}
