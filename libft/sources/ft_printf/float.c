/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:27:05 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 13:18:26 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_round(t_parse *parse, double f)
{
	int		i;

	i = 0;
	f *= 10;
	while (parse->str[i] && parse->str[i] != '.')
		i++;
	i += parse->precision;
	while (f > 5 && i && parse->str[i] == '9')
	{
		parse->str[i] = '0';
		i--;
	}
	if (parse->str[i] == '.')
		i--;
	if (f > 5 && parse->str[i] != '9')
		parse->str[i] += 1;
	if (!parse->precision && !(parse->flags & HASHTAG))
	{
		i = 0;
		while (parse->str[i] && parse->str[i] != '.')
			i++;
		if (!(parse->str = ft_strndupfree(parse->str, i)))
			return ;
	}
}

static void	ft_float(t_parse *parse, double f)
{
	char	*str;
	int		i;

	i = 0;
	if (!(parse->str = ft_strjoinfree(ft_lltoa_base(f, 10), ".", 1)))
		return ;
	f -= ft_atoi(parse->str);
	while (f && i < parse->precision)
	{
		f *= 10;
		if (!(str = ft_lltoa_base(f, 10)))
			return ;
		if (!(parse->str = ft_strjoinfree(parse->str, str, 1)))
			return ;
		f -= ft_atoi(str);
		ft_strdel(&str);
		i++;
	}
	ft_round(parse, f);
}

static void	ft_inf_nan(t_parse *parse, double f)
{
	if (f != f)
		if (!(parse->str = ft_strdup("nan")))
			return ;
	if (f && f == f / 2)
		if (!(parse->str = ft_strdup("inf")))
			return ;
	if (parse->str)
		parse->precision = 0;
}

void		ft_type_float(va_list args, t_parse *parse)
{
	long double	f;
	int			sign;
	char		*str;
	t_dparts	d;

	if (parse->precision == -1)
		parse->precision = 6;
	f = (parse->sub_specifier == 'D') ? va_arg(args, long double)
		: va_arg(args, double);
	d.d = f;
	sign = (d.p.sign & 1) ? -1 : 1;
	if (sign == -1)
		parse->flags |= NEGATIVE;
	ft_inf_nan(parse, f);
	f *= sign;
	if (!parse->str)
		ft_float(parse, f);
	if (sign == -1)
	{
		if (!(str = ft_strjoin("-", parse->str)))
			return ;
		ft_strdel(&parse->str);
		parse->str = str;
	}
}
