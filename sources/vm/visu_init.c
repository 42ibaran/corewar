/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 14:20:59 by ephe              #+#    #+#             */
/*   Updated: 2019/09/08 13:00:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static int	init_text_tiles(t_visu *sdl)
{
	char		*tmp;
	int			i;

	sdl->color_tab[0] = (SDL_Color)MY_RED;
	sdl->color_tab[1] = (SDL_Color)MY_GREEN;
	sdl->color_tab[2] = (SDL_Color)MY_BLUE;
	sdl->color_tab[3] = (SDL_Color)MY_YELLOW;
	sdl->color_tab[4] = (SDL_Color)MY_GREY;
	if (!(sdl->font = TTF_OpenFont("./fonts/VCR_OSD_MONO_1.001.ttf", 300))
		|| !(tmp = ft_strdup("0")))
		return (0);
	i = -1;
	while (++i < 80)
	{
		tmp[0] = (i % 16) < 10 ? i % 16 + '0' : i % 16 + 87;
		if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, tmp,
			sdl->color_tab[i % 5])) || !(sdl->text_tab[i % 5][i % 16] =
			SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface)))
			return (0);
		SDL_FreeSurface(sdl->surface);
	}
	free(tmp);
	TTF_CloseFont(sdl->font);
	return (1);
}

static int	init_player(t_visu *sdl)
{
	if (!(sdl->font = TTF_OpenFont("./fonts/batmfo__.ttf", 300)))
		return (0);
	if (!(sdl->surface = TTF_RenderText_Solid(sdl->font, "Players",
		sdl->color_tab[4])))
		return (0);
	if (!(sdl->player = SDL_CreateTextureFromSurface(sdl->renderer,
		sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	TTF_CloseFont(sdl->font);
	return (1);
}

static int	init_champ_names(t_vm *v, t_visu *sdl)
{
	int			i;

	if (!(sdl->font = TTF_OpenFont("./fonts/batmfa__.ttf", 300)))
		return (0);
	i = -1;
	while (++i < v->nb_players)
	{
		if (!(sdl->surface = TTF_RenderText_Solid(sdl->font,
			v->players[i].head.name, sdl->color_tab[i])))
			return (0);
		if (!(sdl->champ_names[i] = SDL_CreateTextureFromSurface(sdl->renderer,
			sdl->surface)))
			return (0);
		SDL_FreeSurface(sdl->surface);
	}
	TTF_CloseFont(sdl->font);
	return (1);
}

int			open_visu(t_vm *v, t_visu *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO))
		exit_fail(v, sdl, NULL, 1);
	sdl->running = 1;
	sdl->sdl_on = 1;
	if (!(sdl->window = SDL_CreateWindow("CORE PAS WAR", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 2560, 1440, SDL_WINDOW_SHOWN))
		|| !(sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_ACCELERATED)))
		exit_fail(v, sdl, NULL, 1);
	if (TTF_Init())
		exit_fail(v, sdl, NULL, 1);
	sdl->ttf_on = 1;
	sdl->step = 12;
	sdl->nb_proc_alive = v->nb_players;
	if (!init_text_tiles(sdl) || !init_legend(sdl) || !init_player(sdl)
		|| !init_champ_names(v, sdl))
		exit_fail(v, sdl, NULL, 1);
	return (1);
}
