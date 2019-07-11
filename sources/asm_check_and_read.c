/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_and_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/11 17:28:56 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "corewar.h"

int		check_args(int ac, char **av)
{
	char	*pos;

	if (ac == 1)
		error(-1);
	pos = ft_strstr(av[ac - 1], ".s");
	if (!pos || ft_strcmp(pos, ".s") || pos == av[ac - 1])
		error (-1);
	return (open(av[ac - 1], O_RDONLY));
}

void	define_and_remember(char *line, int j, int i)
{
	if (j > i)
		return ;
	if (line[j] == LABEL_CHAR)
		ft_printf(" LABEL ");
	if (line[j] == 'r')
		ft_printf(" REGISTER ");
	if (line[j] == DIRECT_CHAR)
		ft_printf(" DIRECT ");
	if (line[j] == SEPARATOR_CHAR)
		ft_printf(" SEPARATOR ");
	define_and_remember(line, j + 1, i);
}

void	lex(char *line, int i, int j)
{
	static char		quote = 0;
	char			prev_quote;

	prev_quote = quote;
	if (!line[i])
	{
		write(1, "\n", 1);
		return ;
	}
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == COMMENT_CHAR
				|| line[i] == SEPARATOR_CHAR
				|| line[i] == ' '
				|| line[i] == '\t')
			break ;
		if (line[i] == '"')
			quote = (quote == 0 ? 1 : 0);
		write(1, &line[i], 1);
		i++;
	}
	write(1, "*", 1);
	if (!quote && !prev_quote)
	{
		define_and_remember(line, j, i - 1);
		define_and_remember(line, i, i);
	}
	if (line[i] == COMMENT_CHAR)
	{
		write(1, "\n", 1);
		return ;
	}
	lex(line, i + 1, i + 1);
}

void	check_and_read(int ac, char **av)
{
	int		fd;
	char	*line;
	
	if ((fd = check_args(ac, av)) >= 0)
	{
		
		while (get_next_line(fd, &line) == 1)
		{
			lex(line, 0, 0);
			//ft_printf("%s", line);
			free(line);
		}
	}
	else
		error(-2);
}
