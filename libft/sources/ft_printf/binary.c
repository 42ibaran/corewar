/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:24:46 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:49:30 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_type_bin(va_list args, t_parse *parse)
{
	long long	i;

	i = 0;
	if (parse->sub_specifier == 'H')
		i = (char)va_arg(args, int);
	else if (parse->sub_specifier == 'h')
		i = (short)va_arg(args, int);
	else if (parse->sub_specifier == 'L')
		i = va_arg(args, long long);
	else if (parse->sub_specifier == 'l')
		i = va_arg(args, long);
	else if (parse->sub_specifier == '\0')
		i = va_arg(args, int);
	if (i < 0)
		parse->flags |= NEGATIVE;
	if (!(parse->str = ft_lltoa_base(i, 2)))
		return ;
}
