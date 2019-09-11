/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_un_lltoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 17:26:22 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:44:25 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_un_lltoa_base(unsigned long long n, int base)
{
	char				*str;
	unsigned long long	i;
	int					len;

	len = 0;
	if (n == 0 || base == 0)
		return (ft_strdup("0"));
	i = n;
	while (i > 0)
	{
		i /= base;
		len++;
	}
	if (!(str = ft_strnew(len)))
		return (0);
	while (0 < len--)
	{
		if (n % base < 10)
			str[len] = n % base + '0';
		else
			str[len] = n % base + 'a' - 10;
		n = n / base;
	}
	return (str);
}
