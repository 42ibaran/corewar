/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:47:35 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 16:40:11 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

int	verbose(int argc, char **argv, t_parse_argv *av, t_vm *v)
{
	if (av->is_verbose)
		return (ft_usage());
	av->is_verbose = 1;
	if ((v->verbose = ft_number(argc, argv, av)) < 0)
		return (ft_usage());
	return (0);
}

int	dump(int argc, char **argv, t_parse_argv *av, t_vm *v)
{
	if (av->is_dump)
		return (ft_usage());
	av->is_dump = 1;
	v->dirty = 0;
	if ((v->dump_cycle = ft_number(argc, argv, av)) < 0)
		return (ft_usage());
	return (0);
}

int	dirty(int argc, char **argv, t_parse_argv *av, t_vm *v)
{
	if (av->is_dump)
		return (ft_usage());
	av->is_dump = 1;
	v->dirty = 1;
	if ((v->dump_cycle = ft_number(argc, argv, av)) < 0)
		return (ft_usage());
	return (0);
}

int	num_champ(int argc, char **argv, t_parse_argv *av, t_vm *v)
{
	(void)v;
	av->nb_champ = ft_number(argc, argv, av);
	if (av->bool)
		return (ft_usage());
	av->count_nb++;
	av->is_nb = 1;
	return (0);
}

int	init_visu(int argc, char **argv, t_parse_argv *av, t_vm *v)
{
	(void)argc;
	(void)argv;
	if (av->is_visu || av->is_verbose || av->is_dump)
		return (ft_usage());
	av->is_visu = 1;
	v->visu = 1;
	av->is_verbose = 1;
	v->verbose = 0;
	av->is_dump = 1;
	v->dump_cycle = -1;
	return (0);
}
