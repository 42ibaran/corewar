/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:14:09 by dadler            #+#    #+#             */
/*   Updated: 2019/09/02 17:24:32 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdint.h>

int16_t	reverser_16(int16_t a)
{
	return (((a & 0xFF00) >> 8) | ((a & 0x00FF) << 8));
}

int32_t	reverser_32(int32_t a)
{
	int32_t tmp;

	tmp = 0;
	tmp = ((a & 0xFF000000) >> 24) | ((a & 0x00FF) << 24);
	tmp |= ((a & 0x00FF0000) >> 8) | ((a & 0x0000FF00) << 8);
	return (tmp);
}

int		read_ind(t_vm *v, int pos, int size)
{
	int	val;

	val = 0;
	while (size--)
		val |= (unsigned char)v->f.field[get_offset(pos + size)] << (size * 8);
	return (val);
}

void	write_ind(char mem[], int pos, int val, int size)
{
	while (size--)
		mem[get_offset(pos + size)] = (char)(val >> (size * 8));
}

void	write_ind_owner(char mem[], int pos, int val, int size)
{
	while (size--)
		mem[get_offset(pos + size)] = (char)val;
}
