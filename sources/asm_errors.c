/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:12:14 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 14:57:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			error(char code)
{
	if (code == ERR_MEMORY)
		ft_printf("Error: can't allocate memory\n");
	else if (code == ERR_COMMON)
		ft_printf("Error\n");
	else if (code == ERR_USAGE)
		ft_printf("usage: ./asm filename.s\n");
	else if (code == ERR_READ)
		ft_printf("Error: can't open source file\n");
	else if (code == ERR_WRITE)
		ft_printf("Error: can't open/create output file\n");
	else if (code == ERR_MAGIC)
		ft_printf("Error: invalid magic header\n");
	else if (code == ERR_END)
		ft_printf("Error: unexpected end of file\n");
	f_free();
	exit(EXIT_FAILURE);
}

static void		lex_error_next(char code, char *instr)
{
	if (code == ERR_INVALID_ARG)
		ft_printf("Error [Line %d]: invalid argument '%s'\n",
			g_input_l, instr);
	else if (code == ERR_INV_REGISTER)
		ft_printf("Error [Line %d]: invalid register\n", g_input_l);
	else if (code == ERR_NO_NAME_OR_COMMENT)
		ft_printf("Error [Line %d]: no name and/or comment\n", g_input_l);
	else if (code == ERR_NAME_TOO_LONG)
		ft_printf("Error [Line %d]: name too long\n", g_input_l);
	else if (code == ERR_COMMENT_TOO_LONG)
		ft_printf("Error [Line %d]: comment too long\n", g_input_l);
	else if (code == ERR_NAME_EXISTS)
		ft_printf("Error [Line %d]: name already exists\n", g_input_l);
	else if (code == ERR_COMMENT_EXISTS)
		ft_printf("Error [Line %d]: comment already exists\n", g_input_l);
}

void			lex_error(char code, char *instr)
{
	if (code == ERR_TOO_MANY_ARGS)
		ft_printf("Error [Line %d]: too many arguments for instruction '%s'\n",
			g_input_l, instr);
	if (code == ERR_NOT_ENOUGH_ARGS)
		ft_printf("Error [Line %d]: too few arguments for instruction '%s'\n",
			g_input_l, instr);
	else if (code == ERR_SEPARATOR)
		ft_printf("Error [Line %d]: expected separator for instruction '%s'\n",
			g_input_l, instr);
	else if (code == ERR_WRONG_ARG_TYPE)
		ft_printf("Error [Line %d]: wrong argument type for instruction '%s'\n",
			g_input_l, instr);
	else if (code == ERR_UNKMOWN_OPERATION)
		ft_printf("Error [Line %d]: unknown operation '%s'\n",
			g_input_l, instr);
	else if (code == ERR_UNEXPECTED_TOKEN)
		ft_printf("Error [Line %d]: unexpected token '%s'\n",
			g_input_l, instr);
	else if (code == ERR_UNKNOWN_LABEL)
		ft_printf("Error [Line %d]: unknown label '%s'\n",
			g_input_l, instr);
	else
		lex_error_next(code, instr);
	f_free();
	exit(EXIT_FAILURE);
}
