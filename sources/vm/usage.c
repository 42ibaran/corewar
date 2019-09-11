/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:55:03 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_usage(void)
{
	ft_putstr("Usage: ./corewar [-v number] [-dump nbr_cycles] [[-n number]");
	ft_putendl(" champion1.cor] ...");
	ft_putstr("       -v number: Verbosity levels, can be added together to");
	ft_putendl(" enable several");
	ft_putendl("             - 0: Show only essentials");
	ft_putendl("             - 1: Show lives");
	ft_putendl("             - 2: Show cycles");
	ft_putstr("             - 4: Show operations (Params are NOT litteral)");
	ft_putendl(" ...)");
	ft_putendl("             - 8: Show deaths");
	ft_putendl("             - 16: Show PC movements (Except for jumps)");
	ft_putstr("       -dump nbr_cycles: at the end of nbr_cycles of");
	ft_putendl(" executions,");
	ft_putendl("             dump the memory on the standard");
	ft_putendl("       -d nbr_cycles: at the end of nbr_cycles of executions,");
	ft_putendl("            dump the memory on the standard (zaz's vm format)");
	ft_putendl("       output and quit the game");
	ft_putendl("       -n number: sets the number of the next player");
	ft_putendl("       -visu: SDL output mode");
	return (-1);
}
