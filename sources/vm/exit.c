/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadler <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:31:06 by dadler            #+#    #+#             */
/*   Updated: 2019/09/06 14:10:07 by dadler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

int		exit_fail(t_vm *v, t_visu *sdl, t_param *param_tab, int free_list)
{
	if (sdl)
		destroy_visu(v, sdl);
	if (param_tab)
		free(param_tab);
	if (v)
	{
		if (free_list)
			free_proc_list(v);
		free(v);
	}
	exit(EXIT_FAILURE);
	return (-1);
}
