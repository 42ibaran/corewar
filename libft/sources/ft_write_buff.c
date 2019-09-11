/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 13:38:55 by ephe              #+#    #+#             */
/*   Updated: 2019/08/12 14:18:26 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_copy_buff(char buff[], char *line, int *i, int *j)
{
	while (*i < 4096 && line[*j])
	{
		buff[*i] = line[*j];
		*j += 1;
		*i += 1;
	}
}

char		*ft_write_buff(char *line, int *i)
{
	static char	buff[4096];
	int			j;

	j = 0;
	if (*i == -1)
	{
		ft_putendl(buff);
		return (0);
	}
	if (!line)
		return (0);
	if (!*i)
		ft_bzero(buff, 4096);
	ft_copy_buff(buff, line, i, &j);
	if (*i == 4096 && line[j])
	{
		write(1, buff, 4096);
		ft_bzero(buff, 4096);
		*i = 0;
		ft_copy_buff(buff, line, i, &j);
	}
	return (buff);
}
