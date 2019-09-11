/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:34:27 by ephe              #+#    #+#             */
/*   Updated: 2019/06/10 13:34:46 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_lltoa_base(long long n, int base)
{
	char	buff[sizeof(long long) * 8 + 1];
	int		i;
	int		sign;
	int		tmp;

	i = sizeof(long long) * 8 - 1;
	buff[i + 1] = '\0';
	sign = n < 0 ? 1 : 0;
	if (!n)
		return (ft_strdup("0"));
	if (base < 2 || base > 16)
		base = 10;
	while (n)
	{
		tmp = n % base < 0 ? -(n % base) : n % base;
		buff[i] = tmp < 10 ? tmp + '0' : tmp + 'a' - 10;
		i--;
		n = n / base;
	}
	if (sign == 1)
	{
		buff[i] = '-';
		i--;
	}
	return (ft_strdup(buff + i + 1));
}
