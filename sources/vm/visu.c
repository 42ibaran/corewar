/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 11:13:07 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static int	champ_render(t_vm *v, t_visu *sdl)
{
	int			i;

	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 9, 230, 500, 100};
	if (SDL_RenderCopy(sdl->renderer, sdl->player, NULL, &sdl->rect))
		return (0);
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 9, 350, sdl->step * 30,
		sdl->step * 2};
	i = -1;
	while (++i < v->nb_players)
	{
		sdl->rect.w = sdl->step * ft_strlen(v->players[i].head.name);
		if (SDL_RenderCopy(sdl->renderer, sdl->champ_names[i], NULL,
			&sdl->rect))
			return (0);
		sdl->rect.y += 50;
	}
	sdl->rect = (SDL_Rect){sdl->step, sdl->step, sdl->step - sdl->step / 5,
		sdl->step};
	return (1);
}

int			render_proc_pc(t_vm *v, t_visu *sdl)
{
	t_plist		*tmp;
	SDL_Rect	rect;

	rect = (SDL_Rect){sdl->step, sdl->step, 2 * (sdl->step - sdl->step / 5),
		sdl->step};
	if (SDL_SetRenderDrawColor(sdl->renderer, 225, 225, 225, 75))
		return (0);
	tmp = v->process_list;
	while (tmp)
	{
		rect.y = sdl->step;
		rect.x = sdl->step;
		if (tmp->proc.proc_nb)
		{
			rect.x += (tmp->proc.pc % 64) * (((sdl->step - sdl->step / 3)
				+ sdl->step + sdl->step / 3));
			rect.y += ((tmp->proc.pc / 64) * (sdl->step + sdl->step / 2));
			if (SDL_RenderFillRect(sdl->renderer, &rect))
				return (0);
		}
		tmp = tmp->next;
	}
	if (SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255))
		return (0);
	return (1);
}

static int	visu_loop(t_vm *v, t_visu *sdl)
{
	int			i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (SDL_RenderCopy(sdl->renderer,
			sdl->text_tab[(unsigned char)v->f.owner[i]]
			[(unsigned char)v->f.field[i] / 16], NULL, &sdl->rect))
			return (0);
		sdl->rect.x += sdl->step - sdl->step / 3;
		if (SDL_RenderCopy(sdl->renderer,
			sdl->text_tab[(unsigned char)v->f.owner[i]]
			[(unsigned char)v->f.field[i] % 16], NULL, &sdl->rect))
			return (0);
		if (!((i + 1) % 64))
		{
			sdl->rect.x = sdl->step;
			sdl->rect.y += sdl->step + sdl->step / 2;
		}
		else
			sdl->rect.x += sdl->step + sdl->step / 3;
	}
	return (1);
}

int			visu(t_vm *v, t_visu *sdl)
{
	if (SDL_PollEvent(&sdl->event) && sdl->event.type == SDL_QUIT)
		sdl->running = 0;
	if (!sdl->running)
		return (1);
	if (SDL_SetRenderDrawBlendMode(sdl->renderer, SDL_BLENDMODE_BLEND))
		return (exit_fail(v, sdl, NULL, 1));
	SDL_RenderClear(sdl->renderer);
	sdl->rect = (SDL_Rect){sdl->step, sdl->step, sdl->step - sdl->step / 5,
		sdl->step};
	if (!legend_render(sdl) || !champ_render(v, sdl) || !update_turn(v, sdl)
		|| !visu_loop(v, sdl) || !render_proc_pc(v, sdl))
		return (exit_fail(v, sdl, NULL, 1));
	if (sdl->renderer)
		SDL_RenderPresent(sdl->renderer);
	return (0);
}
