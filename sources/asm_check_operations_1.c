/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 14:52:53 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_args_live(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	check_arg(&word, get_f_arr(200), "live");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, "live");
	oper->arg_nbr = ++arg_nbr;
}

void	check_args_ld(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "ld";
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

void	check_args_st(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "st";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(130), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_add(t_operation *oper, t_word *word)
{
	char	arg_nbr;
	char	*name;

	name = "add";
	arg_nbr = -1;
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_sep(&word, name);
	check_arg(&word, get_f_arr(100), name);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	check_null(&word, name);
	oper->arg_nbr = arg_nbr + 1;
}
