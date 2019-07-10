/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 13:41:28 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/10 14:09:50 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error(char code)
{
	if (code == -1)
		ft_printf("usage: ./asm filename.s\n");
	exit(EXIT_FAILURE);
}

void	check_args(int ac, char **av)
{
	if (ac == 1)
		error(-1);
	else
		ft_printf("%s\n", av[ac - 1]);
}

int		main(int ac, char **av)
{
	check_args(ac, av);
	return (0);
}
