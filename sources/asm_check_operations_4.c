/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 14:54:13 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_args_lld(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "lld";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(230), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lldi(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "lldi";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(123), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(120), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lfork(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "lfork";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(200), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_aff(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "aff";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}
