/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoint128.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:01:10 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/31 14:01:20 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

__int128_t		ft_atoint128(const char *str)
{
	__int128_t		to_return;
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
