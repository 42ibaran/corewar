/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:30:38 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 18:33:07 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	zeros_and_magic(int fd, unsigned int number)
{
	unsigned int	divider;
	char			c;

	divider = 0x1000000;
	while (divider != 0)
	{
		c = number / divider;
		write(fd, &c, 1);
		number %= divider;
		divider /= 0x100;
	}
}

void	code_size(int fd, t_instruction *instr)
{
	unsigned int	size;
	t_operation		*oper;

	size = 0;
	while (instr)
	{
		oper = instr->operation;
		while (oper)
		{
			size += oper->length;
			oper = oper->next;
		}
		instr = instr->next;
	}
	zeros_and_magic(fd, size);
}

void	exec_code(int fd, t_instruction *instr)
{
	t_operation		*oper;

	while (instr)
	{
		oper = instr->operation;
		while (oper)
		{
			write(fd, oper->binary, oper->length);
			oper = oper->next;
		}
		instr = instr->next;
	}
}

/*
** write_into_file() opens/creates file with .cor extention,
** puts magic header, name, 4 zeros, code size, comment, 4 zeros and code
** in it, closes the file and gives the result message
*/

void	write_into_file(t_output *out, char *name)
{
	int		fd;

	if (!out->instr)
		error(ERR_END);
	name[ft_strlen(name) - 2] = '\0';
	name = ft_strjoin(name, ".cor");
	if ((fd = open(name, O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
		error(ERR_WRITE);
	zeros_and_magic(fd, COREWAR_EXEC_MAGIC);
	write(fd, out->champ->name, PROG_NAME_LENGTH);
	zeros_and_magic(fd, 0);
	code_size(fd, out->instr);
	write(fd, out->champ->comment, COMMENT_LENGTH);
	zeros_and_magic(fd, 0);
	exec_code(fd, out->instr);
	close(fd);
	ft_printf("Writing output program to %s\n", name);
	free(name);
}
