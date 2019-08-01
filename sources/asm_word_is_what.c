/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 14:55:05 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	w_is_reg(t_word *word)
{
	return (word->is_register);
}

char	w_is_dir(t_word *word)
{
	return (word->is_direct);
}

char	w_is_indir(t_word *word)
{
	return (word->is_indirect);
}
