/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 15:56:34 by ephe              #+#    #+#             */
/*   Updated: 2019/09/09 15:57:18 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	helper(t_vm *v, t_process p, t_param param, int mod)
{
	int		val;

	if (v->op_tab[p.opc - 1].size && param.direct)
		val = reverser_16(param.val);
	else if (param.direct)
		val = reverser_32(param.val);
	else if (param.indirect)
	{
		val = reverser_16(param.val);
		if (p.opc == 10 || p.opc == 11)
		{
			val = reverser_32(read_ind(v, (p.pc + val % IDX_MOD) % MEM_SIZE,
				IND_SIZE));
			val = mod == 1 ? val % IDX_MOD : val;
		}
		else if (p.opc == 14)
			val = reverser_32(read_ind(v, (p.pc + val) % MEM_SIZE, IND_SIZE));
	}
	else if (param.reg && (p.opc == 10 || p.opc == 11))
		val = p.reg[param.val - 1];
	else
		val = param.val;
	return (val);
}
