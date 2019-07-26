/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_get_label_distance.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 11:31:27 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/26 12:31:01 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			instruction_first(t_operation *oper, t_instruction *instr)
{
	t_operation		*tmp;
	int				dist = 0;

	tmp = instr->operation;
	while (tmp != oper)
	{
		dist += tmp->length;
		tmp = tmp->next;
		if (!tmp)
		{
			instr = instr->next;
			tmp = instr->operation;
		}
	}
	return (-dist);
}

int			operation_first(t_operation *oper, t_instruction *instr,
			t_instruction *prev_instr)
{
	int				dist = 0;
	//oper = oper->next;
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

int			get_label_distance(t_operation *oper, t_instruction *instr,
			char *name)
{
	char			f_label = 0;
	char			f_oper = 0;
	char			label_or_oper = 0;
	t_operation		*inner_oper;
	t_instruction 	*found_instr;
	t_instruction	*prev_instr;

	while (instr)
	{
		inner_oper = instr->operation;
		if (!ft_strncmp(instr->name, name, ft_strlen(name)))
		{
			found_instr = instr;
			label_or_oper = (label_or_oper == 0 ? 1 : label_or_oper);
			f_label = 1;
		}
		while (inner_oper && !f_oper)
		{
			if (inner_oper == oper)
			{
				prev_instr = instr;
				f_oper = 1;
				label_or_oper = (label_or_oper == 0 ? 2 : label_or_oper);
				break ;
			}
			inner_oper = inner_oper->next;
		}
		if (f_label && f_oper)
			break ;
		instr = instr->next;
	}
	if (!instr)
		error(0); //unknown label
	if (label_or_oper == 1)
		return (instruction_first(oper, found_instr));
	else
		return (operation_first(oper, found_instr, prev_instr));
}
