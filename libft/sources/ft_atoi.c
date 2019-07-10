/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:07:23 by ibaran            #+#    #+#             */
/*   Updated: 2019/05/12 17:29:36 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

long long		ft_atoi(const char *str)
{
	long long		to_return;
	int				sign;
	char			*pointer;

	pointer = (char*)str;
	sign = 1;
	to_return = 0;
	while (((*pointer >= 9 && *pointer <= 13) || *pointer == 32))
		pointer++;
	if (*pointer == '-')
	{
		sign = -1;
		pointer++;
	}
	else if (*pointer == '+')
		pointer++;
	while (*pointer >= '0' && *pointer <= '9')
	{
		to_return = (to_return * 10) + (*pointer - 48);
		pointer++;
	}
	return (to_return * sign);
}
