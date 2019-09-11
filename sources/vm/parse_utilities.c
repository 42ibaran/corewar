/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 17:07:48 by ephe              #+#    #+#             */
/*   Updated: 2019/09/09 13:13:40 by dadler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

int		ft_number(int argc, char **argv, t_parse_argv *av)
{
	av->bool = 0;
	av->i++;
	if (av->i >= argc - 1 || (argv[av->i][0] != '-'
		&& !ft_isdigit(argv[av->i][0])) || !ft_isnum(argv[av->i] + 1))
	{
		av->bool = 1;
		av->i--;
		return (-1);
	}
	return (ft_atoi(argv[av->i]));
}

int		wrapper(void *p, char return_error_flag)
{
	ft_memdel(p);
	return (return_error_flag == 1 ? -1 : 0);
}

int32_t	vm_abs(int n)
{
	return (n >= 0 ? n : -n);
}
