/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:07:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/29 19:03:28 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisnum(char *str)
{
	int		i;

	if (!str || !*str)
		return (0);
	if ((*str < '0' || *str > '9') && *str != '+' && *str != '-')
		return (0);
	i = 0;
	if (*str == '+' || *str == '-')
	{
		if (!*(str + 1))
			return (0);
		i++;
	}
	while (str[i] == '0')
		i++;
	// if (ft_strlen(str + i) > 11)
	// 	return (0);
	while (*(++str))
		if ((*str < '0' || *str > '9'))
			return (0);
	return (1);
}
