/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_process_negative_arg_val.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:59:20 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/31 14:56:48 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		invert_bits(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '0')
			str[i] = '1';
		else if (str[i] == '1')
			str[i] = '0';
	}
}

static void		add_one(char *str, int last)
{
	int		i;

	i = last;
	while (--i > -1)
	{
		if (str[i] == '0')
		{
			str[i] = '1';
			break ;
		}
		else
			str[i] = '0';
	}
}

int				process_negative_val(__int128_t val, char arg_size)
{
	char	*bin_str;
	char	*bin_str_16;

	bin_str = ft_itoa_base(-val, 2);
	if ((int)ft_strlen(bin_str) > 8 * arg_size)
		return (val);
	if (!(bin_str_16 = (char*)malloc(sizeof(char) * (8 * arg_size + 1))))
		error(ERR_MEMORY);
	ft_fillstr(bin_str_16, '0', 8 * arg_size);
	ft_strcpy(bin_str_16 + (8 * arg_size - ft_strlen(bin_str)), bin_str);
	invert_bits(bin_str_16);
	add_one(bin_str_16, 8 * arg_size);
	val = ft_atoi_base(bin_str_16, 2);
	free(bin_str_16);
	free(bin_str);
	return (val);
}
