/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:34:56 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:54:27 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <libc.h>
#include "ft_printf.h"

char	*ft_dupexit(const char *src)
{
	char	*cpy;
	int		i;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_ctoaexit(char c)
{
	char	*result;

	if (!(result = (char*)malloc(sizeof(char) * 2)))
		exit(EXIT_FAILURE);
	result[0] = c;
	result[1] = '\0';
	return (result);
}

char	*ft_strndupexit(const char *src, size_t n)
{
	char	*cpy;
	int		i;

	if (!(cpy = (char*)malloc(sizeof(char) * (ft_min(ft_strlen(src), n) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (src[i] != '\0' && n != 0)
	{
		cpy[i] = src[i];
		i++;
		n--;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_nctoaexit(char c, size_t n)
{
	char	*result;
	size_t	i;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (n + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < n)
	{
		result[i] = c;
		i++;
	}
	result[n] = '\0';
	return (result);
}
