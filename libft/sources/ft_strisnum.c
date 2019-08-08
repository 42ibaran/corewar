/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:07:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/08 14:49:06 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** return codes:
** -1 numeric but too long to be an int
** 0 not numeric characters
** 1 length of int and numeric
*/

int		ft_strisnum(char *str)
{
	int		i;
	size_t	len;

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
	len = ft_strlen(str + i);
	while (*(++str))
		if ((*str < '0' || *str > '9'))
			return (0);
	if (len > 20)
		return (-1);
	return (1);
}

int		ft_strisnum_asm(char *str)
{
	int		i;
	size_t	len;

	if (!str || !*str)
		return (0);
	if ((*str < '0' || *str > '9') && *str != '-')
		return (0);
	i = 0;
	if (*str == '-')
	{
		if (!*(str + 1))
			return (0);
		i++;
	}
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	while (*(++str))
		if ((*str < '0' || *str > '9'))
			return (0);
	if (len > 20)
		return (-1);
	return (1);
}
