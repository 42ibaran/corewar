/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:41:28 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/10 15:02:58 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error(char code)
{
	if (code == 0)
		ft_printf("Error\n");
	if (code == -1)
		ft_printf("usage: ./asm filename.s\n");
	if (code == -2)
		ft_printf("Cannot open file\n");
	//f_free();
	exit(EXIT_FAILURE);
}

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

void	check_and_read(int ac, char **av)
{
	int		fd;
	char	*line;
	
	if ((fd = check_args(ac, av)) >= 0)
		while (get_next_line(fd, &line) == 1)
		{
			ft_printf("%s", line);
			free(line);
		}
	else
		error(-2);
}

int		main(int ac, char **av)
{
	check_and_read(ac, av);
	return (0);
}
