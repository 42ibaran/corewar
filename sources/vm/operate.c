/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:15:41 by dadler            #+#    #+#             */
/*   Updated: 2019/09/09 17:00:23 by dadler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void	exec_ops(t_vm *v, t_visu *sdl)
{
	t_plist			*tmp;

	tmp = v->process_list;
	while (tmp)
	{
		set_unset(v, tmp);
		execute_cycle(v, tmp, sdl);
		tmp = tmp->next;
	}
	tmp = v->process_list;
	while (tmp)
	{
		exec_catcher(v, tmp);
		tmp = tmp->next;
	}
}

static void	load_ops(t_vm *v)
{
	if (v->process_list == NULL)
		start_proc_list(v);
}

void		free_proc_list(t_vm *v)
{
	t_plist *tmp;

	while (v->process_list)
	{
		tmp = v->process_list;
		v->process_list = v->process_list->next;
		if (tmp)
			free(tmp);
	}
}

static int	op_loop(t_vm *v, t_visu *sdl)
{
	while (v->nb_proc_alive)//&& v->cycle_to_die > 0)
	{
		if (v->visu && visu(v, sdl))
			break ;
		if (v->verbose & 2)
			ft_printf("It is now cycle %ld\n", v->curr_cycle);
		exec_ops(v, sdl);
		if (v->curr_cycle == v->dump_cycle)
		{
			ft_dump(v);
			exit_fail(v, sdl, NULL, 1);
		}
		if (v->kill_cycle == v->curr_cycle)
			cycles_to_die(v);
		if (v->print_cycles_to_die)
		{
			v->print_cycles_to_die = 0;
			ft_printf("Cycle to die is now %d\n", v->cycle_to_die);
		}
		count_alive(v, sdl, 0);
		v->curr_cycle++;
	}
	return (1);
}

int			operate(t_vm *v)
{
	t_visu	sdl;

	ft_bzero(&sdl, sizeof(t_visu));
	intro(v);
	v->nb_proc_alive = v->nb_players;
	v->last_p_alive = v->nb_players - 1;
	v->print_cycles_to_die = 0;
	load_ops(v);
	if (v->visu)
		open_visu(v, &sdl);
	if (op_loop(v, &sdl) < 0)
		return (-1);
	if (v->visu && sdl.running)
	{
		render_win(v, &sdl);
		while (sdl.running)
			if (SDL_PollEvent(&sdl.event) && sdl.event.type == SDL_QUIT)
				sdl.running = 0;
	}
	destroy_visu(v, &sdl);
	ft_printf("Contestant %d, \"%s\", has won !\n",
		ft_abs(v->players[v->last_p_alive].nb_champ),
			v->players[v->last_p_alive].head.name);
	free_proc_list(v);
	return (1);
}
