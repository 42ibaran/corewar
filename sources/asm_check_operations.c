/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/26 13:01:23 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_args_live(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("live\n");
	word = word->next;
	if (!word || !word->is_direct)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_ld(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("ld\n");
	word = word->next;
	if (!word || (!word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_st(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("st\n");
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_add(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("add\n");
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_sub(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("sub\n");
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_and(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("and\n");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_or(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("or\n");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_xor(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("xor\n");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_zjmp(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("zjmp\n");
	word = word->next;
	if (!word || !word->is_direct)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_ldi(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("ldi\n");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_sti(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("sti\n");
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_fork(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("fork\n");
	word = word->next;
	if (!word || !word->is_direct)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lld(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("lld\n");
	word = word->next;
	if (!word || (!word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lldi(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("lldi\n");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		error(0);
	word = word->next;
	if (!word || !word->is_register)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lfork(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("lfork\n");
	word = word->next;
	if (!word || !word->is_direct)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_aff(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	//ft_printf("aff\n");
	word = word->next;
	if (!word || !word->is_direct)
		error(0);
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		error(0);
	oper->arg_nbr = arg_nbr + 1;
}

