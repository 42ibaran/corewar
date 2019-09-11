/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_legend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:27:18 by ephe              #+#    #+#             */
/*   Updated: 2019/09/08 12:58:15 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	init(t_visu *sdl)
{
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Processes : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[6] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Last alive : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[7] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	return (1);
}

static int	legend(t_visu *sdl)
{
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Cycle delta : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[3] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Max checks : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[4] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Nbr live : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[5] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!init(sdl))
		return (0);
	return (1);
}

int			init_legend(t_visu *sdl)
{
	if (!(sdl->font = TTF_OpenFont("./fonts/batmfo__.ttf", 300))
		|| !(sdl->surface = TTF_RenderText_Solid(sdl->font, "Corewar",
		sdl->color_tab[4]))
		|| !(sdl->legend[0] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	TTF_CloseFont(sdl->font);
	if (!(sdl->font = TTF_OpenFont("./fonts/batmfa__.ttf", 300))
		|| !(sdl->surface = TTF_RenderText_Solid(sdl->font, "Cycle : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[1] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Cycle to die : ",
		sdl->color_tab[4]))
		|| !(sdl->legend[2] = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	if (!legend(sdl))
		return (0);
	TTF_CloseFont(sdl->font);
	return (1);
}

static int	legend_rend(t_visu *sdl)
{
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 25, 120, sdl->step * 11,
		sdl->step * 2};
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[4], NULL, &sdl->rect))
		return (0);
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * 9;
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[5], NULL, &sdl->rect))
		return (0);
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * 11;
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[6], NULL, &sdl->rect))
		return (0);
	return (1);
}

int			legend_render(t_visu *sdl)
{
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 9, 0, 500, 100};
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[0], NULL, &sdl->rect))
		return (0);
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 10, 120, sdl->step * 6,
		sdl->step * 2};
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[1], NULL, &sdl->rect))
		return (0);
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * 12 - 5;
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[2], NULL, &sdl->rect))
		return (0);
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * 11;
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[3], NULL, &sdl->rect))
		return (0);
	sdl->rect.y += sdl->step * 2;
	sdl->rect.w = sdl->step * 10;
	if (SDL_RenderCopy(sdl->renderer, sdl->legend[7], NULL, &sdl->rect))
		return (0);
	if (!legend_rend(sdl))
		return (0);
	return (1);
}
