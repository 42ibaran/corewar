/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:29:16 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:50:24 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_flag_id(int i, t_parse *parse, const char *format)
{
	while (format[i] && ft_strchr("#0-+ ", format[i]))
	{
		if (format[i] == '#')
			parse->flags |= HASHTAG;
		else if (format[i] == '0')
			parse->flags |= ZERO;
		else if (format[i] == '-')
			parse->flags |= MINUS;
		else if (format[i] == '+')
			parse->flags |= PLUS;
		else if (format[i] == ' ')
			parse->flags |= SPACE;
		i++;
	}
	return (i);
}

int		ft_width_id(int i, va_list args, t_parse *parse, const char *format)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (format[i++] == '*')
		parse->width = va_arg(args, int);
	else
	{
		i--;
		while (format[i] && format[i] >= '0' && format[i] <= '9')
		{
			i++;
			j++;
		}
		if (j)
		{
			k = i - j;
			parse->width = ft_atoi(format + k);
		}
	}
	return (i);
}

int		ft_precision_id(int i, va_list args, t_parse *parse,
const char *format)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (format[i] && format[i] == '.')
	{
		i++;
		if (format[i++] == '*')
			parse->precision = va_arg(args, int);
		else
		{
			i--;
			while (format[i] && format[i] >= '0' && format[i] <= '9' && ++j)
				i++;
			if (j)
			{
				k = i - j;
				parse->precision = ft_atoi(format + k);
			}
		}
	}
	else
		parse->precision = -1;
	return (i);
}

int		ft_sub_specifier_id(int i, t_parse *parse, const char *format)
{
	if (format[i] && format[i] == 'h' && format[i + 1] == 'h')
	{
		parse->sub_specifier = 'H';
		i++;
	}
	else if (format[i] && format[i] == 'h')
		parse->sub_specifier = 'h';
	else if (format[i] && format[i] == 'l' && format[i + 1] == 'l')
	{
		parse->sub_specifier = 'L';
		i++;
	}
	else if (format[i] && format[i] == 'l')
		parse->sub_specifier = 'l';
	else if (format[i] && format[i] == 'L')
		parse->sub_specifier = 'D';
	else
		return (i);
	i++;
	return (i);
}

void	ft_specifier_id(int i, va_list args, t_parse *parse,
const char *format)
{
	t_type	*specifier;
	int		j;

	if (!(specifier = (t_type *)malloc(sizeof(t_type) * 11)))
		return ;
	specifier[0] = (t_type){'c', ft_type_char};
	specifier[1] = (t_type){'s', ft_type_str};
	specifier[2] = (t_type){'p', ft_type_ptr};
	specifier[3] = (t_type){'d', ft_type_int};
	specifier[4] = (t_type){'i', ft_type_int};
	specifier[5] = (t_type){'o', ft_type_un_oct};
	specifier[6] = (t_type){'u', ft_type_un_int};
	specifier[7] = (t_type){'x', ft_type_un_hex};
	specifier[8] = (t_type){'X', ft_type_un_hex_up};
	specifier[9] = (t_type){'f', ft_type_float};
	specifier[10] = (t_type){'b', ft_type_bin};
	j = -1;
	while (++j < 11)
		if (format[i] == specifier[j].c)
		{
			specifier[j].f(args, parse);
			parse->specifier = format[i];
		}
	ft_memdel((void*)&specifier);
}
