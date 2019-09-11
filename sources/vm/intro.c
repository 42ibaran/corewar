/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 11:33:29 by dadler            #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	intro(t_vm *v)
{
	int		i;

	i = -1;
	ft_putstr("Introducing contestants...\n");
	while (++i < v->nb_players)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			ft_abs(v->players[i].nb_champ), v->players[i].head.size,
			v->players[i].head.name, v->players[i].head.comment);
	}
}
