/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:12 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_args_live(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_direct)
		lex_error(ERR_WRONG_ARG_TYPE, "live");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "live");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_ld(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "ld");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "ld");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "ld");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "ld");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_st(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "st");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "st");
	word = word->next;
	if (!word || (!word->is_register && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "st");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "st");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_add(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "add");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "add");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "add");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "add");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "add");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "add");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_sub(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "sub");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "sub");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "sub");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "sub");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "sub");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "sub");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_and(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "and");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "and");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "and");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "and");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "and");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "and");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_or(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "or");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "or");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "or");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "or");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "or");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "or");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_xor(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "xor");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "xor");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "xor");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "xor");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "xor");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "xor");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_zjmp(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_direct)
		lex_error(ERR_WRONG_ARG_TYPE, "zjmp");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "zjmp");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_ldi(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "ldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "ldi");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		lex_error(ERR_WRONG_ARG_TYPE, "ldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "ldi");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "ldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "ldi");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_sti(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "sti");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "sti");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "sti");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "sti");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		lex_error(ERR_WRONG_ARG_TYPE, "sti");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "sti");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_fork(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_direct)
		lex_error(ERR_WRONG_ARG_TYPE, "fork");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "fork");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lld(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "lld");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "lld");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "lld");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "lld");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lldi(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct && !word->is_indirect))
		lex_error(ERR_WRONG_ARG_TYPE, "lldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "lldi");
	word = word->next;
	if (!word || (!word->is_register && !word->is_direct))
		lex_error(ERR_WRONG_ARG_TYPE, "lldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (!word || !word->is_separator)
		lex_error(ERR_SEPARATOR, "lldi");
	word = word->next;
	if (!word || !word->is_register)
		lex_error(ERR_WRONG_ARG_TYPE, "lldi");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "lldi");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_lfork(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_direct)
		lex_error(ERR_WRONG_ARG_TYPE, "lfork");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "lfork");
	oper->arg_nbr = arg_nbr + 1;
}

void	check_args_aff(t_operation *oper, t_word *word)
{
	char	arg_nbr;

	arg_nbr = -1;
	word = word->next;
	if (!word || !word->is_direct)
		lex_error(ERR_WRONG_ARG_TYPE, "aff");
	fill_arg_type(oper, word, ++arg_nbr);
	oper->arg_str[(int)arg_nbr] = word->str;
	word = word->next;
	if (word)
		lex_error(ERR_TOO_MANY_ARGS, "aff");
	oper->arg_nbr = arg_nbr + 1;
}

