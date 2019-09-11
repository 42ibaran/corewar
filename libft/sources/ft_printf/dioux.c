/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dioux.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:32:46 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:49:55 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_type_int(va_list args, t_parse *parse)
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
	else if (i == 0)
		parse->zero = 1;
	if (!(parse->str = ft_lltoa_base(i, 10)))
		return ;
}

void	ft_type_un_int(va_list args, t_parse *parse)
{
	unsigned long long	i;

	i = 0;
	if (parse->sub_specifier == 'H')
		i = (unsigned char)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'h')
		i = (unsigned short)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'L')
		i = va_arg(args, unsigned long long);
	else if (parse->sub_specifier == 'l')
		i = va_arg(args, unsigned long);
	else if (parse->sub_specifier == '\0')
		i = va_arg(args, unsigned int);
	if (i == 0)
		parse->zero = 1;
	if (!(parse->str = ft_lltoa_base(i, 10)))
		return ;
}

void	ft_type_un_oct(va_list args, t_parse *parse)
{
	unsigned long long	i;

	i = 0;
	if (parse->sub_specifier == 'H')
		i = (unsigned char)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'h')
		i = (unsigned short)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'L')
		i = va_arg(args, unsigned long long);
	else if (parse->sub_specifier == 'l')
		i = va_arg(args, unsigned long);
	else if (parse->sub_specifier == '\0')
		i = va_arg(args, unsigned int);
	if (i == 0)
		parse->zero = 1;
	if (!(parse->str = ft_un_lltoa_base(i, 8)))
		return ;
}

void	ft_type_un_hex(va_list args, t_parse *parse)
{
	unsigned long long	i;

	i = 0;
	if (parse->sub_specifier == 'H')
		i = (unsigned char)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'h')
		i = (unsigned short)va_arg(args, unsigned int);
	else if (parse->sub_specifier == 'L')
		i = va_arg(args, unsigned long long);
	else if (parse->sub_specifier == 'l')
		i = va_arg(args, unsigned long);
	else if (parse->sub_specifier == '\0')
		i = va_arg(args, unsigned int);
	if (i == 0)
		parse->zero = 1;
	if (!(parse->str = ft_un_lltoa_base(i, 16)))
		return ;
}

void	ft_type_un_hex_up(va_list args, t_parse *parse)
{
	int	i;

	i = 0;
	ft_type_un_hex(args, parse);
	while (parse->str[i])
	{
		parse->str[i] = ft_toupper(parse->str[i]);
		i++;
	}
}
