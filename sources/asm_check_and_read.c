/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_and_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/10 16:49:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

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

void	lex(char *line)
{
	
}

void	check_and_read(int ac, char **av)
{
	int		fd;
	char	*line;
	
	if ((fd = check_args(ac, av)) >= 0)
		while (get_next_line(fd, &line) == 1)
		{
			lex(line);
			ft_printf("%s", line);
			free(line);
		}
	else
		error(-2);
}
