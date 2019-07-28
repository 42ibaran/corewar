/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:12:14 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:20 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error(char code)
{
	if (code == ERR_MEMORY)
		ft_printf("Error: Can't allocate memory\n");
	else if (code == ERR_COMMON)
		ft_printf("Error\n");
	else if (code == ERR_USAGE)
		ft_printf("usage: ./asm filename.s\n");
	else if (code == ERR_READ)
		ft_printf("Error: Can't open source file\n");
	else if (code == ERR_WRITE)
		ft_printf("Error: Can't open/create output file\n");
	else if (code == ERR_MAGIC)
		ft_printf("Error: Invalid magic header\n");

	//f_free();
	exit(EXIT_FAILURE);
}

void	lex_error(char code, char *instr)
{
	if (code == ERR_INV_REGISTER)
		ft_printf("Error [Line %d]: wrong register\n", g_input_line);
	else if (code == ERR_TOO_MANY_ARGS)
		ft_printf("Error [Line %d]: too many arguments for instruction %s\n",
			g_input_line, instr);
	else if (code == ERR_SEPARATOR)
		ft_printf("Error [Line %d]: expected separator for instruction %s\n",
			g_input_line, instr);
	else if (code == ERR_WRONG_ARG_TYPE)
		ft_printf("Error [Line %d]: wrong argument type for instruction %s\n",
			g_input_line, instr);
	else if (code == ERR_UNKNOWN_LABEL)
		ft_printf("Error [Line %d]: unknown label %s\n", g_input_line, instr);
	else if (code == ERR_NO_NAME_OR_COMMENT)
		ft_printf("Error [Line %d]: no name and/or comment\n", g_input_line);
	else if (code == ERR_NAME_TOO_LONG)
		ft_printf("Error [Line %d]: name too long\n", g_input_line);
	else if (code == ERR_COMMENT_TOO_LONG)
		ft_printf("Error [Line %d]: comment too long\n", g_input_line);
	else if (code == ERR_NAME_EXISTS)
		ft_printf("Error [Line %d]: name already exists\n", g_input_line);
	else if (code == ERR_COMMENT_EXISTS)
		ft_printf("Error [Line %d]: comment already exists\n", g_input_line);
	//f_free();
	exit(EXIT_FAILURE);
}
