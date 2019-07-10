/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:28:45 by ibaran            #+#    #+#             */
/*   Updated: 2019/05/13 11:51:37 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include "libft.h"

char			*ft_strjoinfree(char *s1, char *s2, int n)
{
	char			*result;
	unsigned int	i;

	if (n < 1 || n > 3)
		return (NULL);
	if (!(result = (char*)malloc(sizeof(char) *
		(ft_strlen(s2) + ft_strlen(s1) + 1))))
		return (NULL);
	ft_strcpy(result, s1);
	i = 0;
	while (result[i])
		i++;
	ft_strcpy(result + i, s2);
	if (n == 1 || n == 3)
		free(s1);
	if (n == 2 || n == 3)
		free(s2);
	return (result);
}
