/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 14:27:41 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

int	destroy_visu(t_vm *v, t_visu *sdl)
{
	int		i;

	i = -1;
	while (++i < 80)
		if (sdl->text_tab[i % 5][i % 16])
			SDL_DestroyTexture(sdl->text_tab[i % 5][i % 16]);
	i = -1;
	while (++i < 7)
		if (sdl->legend[i])
			SDL_DestroyTexture(sdl->legend[i]);
	i = -1;
	while (++i < v->nb_players)
		if (sdl->champ_names[i])
			SDL_DestroyTexture(sdl->champ_names[i]);
	if (sdl->player)
		SDL_DestroyTexture(sdl->player);
	if (sdl->renderer)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->window)
		SDL_DestroyWindow(sdl->window);
	if (sdl->ttf_on)
		TTF_Quit();
	if (sdl->sdl_on)
		SDL_Quit();
	return (1);
}

int	render_win(t_vm *v, t_visu *sdl)
{
	SDL_Texture	*win;

	if (!(sdl->font = TTF_OpenFont("./srcs_vm/batmfo__.ttf", 300))
		|| !(sdl->surface = TTF_RenderText_Solid(sdl->font, "WINNER",
		sdl->color_tab[4])))
		return (0);
	TTF_CloseFont(sdl->font);
	if (!(win = SDL_CreateTextureFromSurface(sdl->renderer, sdl->surface)))
		return (0);
	SDL_FreeSurface(sdl->surface);
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 9, 550, 500, 100};
	if (SDL_RenderCopy(sdl->renderer, win, NULL, &sdl->rect))
		return (0);
	sdl->rect = (SDL_Rect){MEM_SIZE / 2 - MEM_SIZE / 9, 650,
		sdl->step * ft_strlen(v->players[v->last_p_alive].head.name) * 2, 100};
	if (SDL_RenderCopy(sdl->renderer, sdl->champ_names[v->last_p_alive], NULL,
		&sdl->rect))
		return (0);
	SDL_DestroyTexture(win);
	if (sdl->renderer)
		SDL_RenderPresent(sdl->renderer);
	return (1);
}
