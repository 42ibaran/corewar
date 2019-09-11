/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndupfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:30:25 by ephe              #+#    #+#             */
/*   Updated: 2019/06/18 17:31:23 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndupfree(const char *s, size_t n)
{
	char			*dup;
	unsigned int	i;

	i = 0;
	if (!(dup = ft_strnew(n)))
	{
		free((char*)s);
		return (0);
	}
	while (i < n)
	{
		dup[i] = s[i];
		i++;
	}
	free((char*)s);
	return (dup);
}
