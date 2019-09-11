/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_cycles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 14:19:10 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static int	update_cycle(t_visu *sdl, int val)
{
	char	*str;
	int		i;

	if (!(str = ft_itoa(val)))
		return (0);
	i = -1;
	while (str[++i])
	{
		if (SDL_RenderCopy(sdl->renderer, sdl->text_tab[4][str[i] - '0'], NULL,
			&sdl->rect))
			return (0);
		sdl->rect.x += sdl->step;
	}
	free(str);
	return (1);
}

static int	update(t_vm *v, t_visu *sdl)
{
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 25 + sdl->step * 11;
	sdl->rect.y += sdl->step * 2;
	if (!update_cycle(sdl, sdl->nb_proc_alive))
		return (0);
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 25;
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * ft_strlen(v->players[v->last_p_alive].head.name);
	if (SDL_RenderCopy(sdl->renderer, sdl->champ_names[v->last_p_alive], NULL,
		&sdl->rect))
		return (0);
	sdl->rect = (SDL_Rect){sdl->step, sdl->step, sdl->step, sdl->step};
	return (1);
}

int			update_turn(t_vm *v, t_visu *sdl)
{
	sdl->rect.h = sdl->step * 2 - 5;
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 10 + sdl->step * 6;
	sdl->rect.y = 121;
	if (!update_cycle(sdl, v->curr_cycle))
		return (0);
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 10 + sdl->step * 12 - 5;
	sdl->rect.y += sdl->step * 2;
	if (!update_cycle(sdl, v->cycle_to_die))
		return (0);
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 10 + sdl->step * 11;
	sdl->rect.y += sdl->step * 2;
	if (!update_cycle(sdl, CYCLE_DELTA))
		return (0);
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 25 + sdl->step * 11;
	sdl->rect.y = 121;
	if (!update_cycle(sdl, MAX_CHECKS))
		return (0);
	sdl->rect.x = MEM_SIZE / 2 - MEM_SIZE / 25 + sdl->step * 9;
	sdl->rect.y += sdl->step * 2;
	if (!update_cycle(sdl, NBR_LIVE))
		return (0);
	update(v, sdl);
	return (1);
}
