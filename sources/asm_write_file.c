/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:30:38 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/29 14:22:17 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	magic(int fd)
{
	unsigned int	magic_n;
	unsigned int	divider;
	char			c;

	divider = 0x1000000;
	magic_n = COREWAR_EXEC_MAGIC;
	while (divider != 0)
	{
		c = magic_n / divider;
		write(fd, &c, 1);
		magic_n %= divider;
		divider /= 0x100;
	}
}

void	zero(int fd, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		write(fd, "\0", 1);
		i++;
	}
}

void	code_size(int fd, t_instruction *instr)
{
	int				size;
	t_operation		*oper;
	unsigned int	divider;
	char			c;

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
	divider = 0x1000000;
	while (divider != 0)
	{
		c = size / divider;
		write(fd, &c, 1);
		size %= divider;
		divider /= 0x100;
	}
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

void	write_into_file(t_output *out, char *name)
{
	int		fd;

	if (!out->instr)
		error(ERR_END);
	name[ft_strlen(name) - 2] = '\0';
	name = ft_strjoin(name, ".cor");
	if ((fd = open(name, O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
		error(ERR_WRITE);
	magic(fd);
	write(fd, out->champ->name, PROG_NAME_LENGTH);
	zero(fd, 4);
	code_size(fd, out->instr);
	write(fd, out->champ->comment, COMMENT_LENGTH);
	zero(fd, 4);
	exec_code(fd, out->instr);
	close(fd);
	ft_printf("Writing output program to %s\n", name);
	free(name);
}
