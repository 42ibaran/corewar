/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_field.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 17:07:04 by dadler            #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void	load_champions(t_vm *v)
{
	int		i;

	i = -1;
	while (++i < v->nb_players)
	{
		ft_memcpy(v->f.field + (i * MEM_SIZE / v->nb_players),
				v->players[i].prog, v->players[i].head.size);
		ft_memset(v->f.owner + (i * MEM_SIZE / v->nb_players), i,
				v->players[i].head.size);
	}
}

int			load_field(t_vm *v)
{
	ft_memset(v->f.field, 0, MEM_SIZE);
	ft_memset(v->f.owner, 4, MEM_SIZE);
	load_champions(v);
	return (1);
}
