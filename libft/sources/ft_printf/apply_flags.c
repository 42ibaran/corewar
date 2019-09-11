/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:45:23 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:49:44 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_flags(t_parse *parse, char *str)
{
	if (parse->flags & HASHTAG && parse->specifier == 'o'
		&& parse->str[0] != '0')
	{
		ft_strdel(&parse->str);
		if (!(parse->str = ft_strjoin("0", str)))
			return ;
	}
	else if (parse->flags & HASHTAG && parse->specifier == 'x'
		&& parse->precision)
	{
		ft_strdel(&parse->str);
		if (!(parse->str = ft_strjoin("0x", str)))
			return ;
	}
	else if (parse->flags & HASHTAG && parse->specifier == 'X'
		&& parse->precision)
	{
		ft_strdel(&parse->str);
		if (!(parse->str = ft_strjoin("0X", str)))
			return ;
	}
}

void		ft_apply_flags(t_parse *parse, char *str)
{
	if (parse->str && parse->flags)
	{
		if (!(str = ft_strdup(parse->str)))
			return ;
		ft_flags(parse, str);
		if (parse->flags & PLUS && !(parse->flags & NEGATIVE)
			&& ft_strchr("difb", parse->specifier))
		{
			ft_strdel(&parse->str);
			if (!(parse->str = ft_strjoin("+", str)))
				return ;
		}
		if (parse->flags & SPACE && !(parse->flags & NEGATIVE)
			&& ft_strchr("difb", parse->specifier))
		{
			ft_strdel(&parse->str);
			if (!(parse->str = ft_strjoin(" ", str)))
				return ;
		}
		ft_strdel(&str);
	}
}

static void	ft_float(t_parse *parse)
{
	int		i;
	int		zero;
	char	tmp;

	i = 0;
	zero = 0;
	if (parse->str && ft_strchr(parse->str, '0') && parse->specifier == 'f'
		&& parse->precision == 0 && parse->flags & ZERO && parse->flags & SPACE
		&& !(parse->flags & NEGATIVE || (parse->flags & PLUS)))
	{
		while (parse->str[zero] && parse->str[zero] != '0')
			zero++;
		while (parse->str[i] && parse->str[i] != ' ')
			i++;
		if (i > zero)
		{
			tmp = parse->str[i];
			parse->str[i] = parse->str[zero];
			parse->str[zero] = tmp;
		}
	}
}

void		ft_apply_sign(t_parse *parse)
{
	int		i;
	int		zero;
	char	tmp;

	i = 0;
	zero = 0;
	ft_float(parse);
	if (parse->str && ft_strchr(parse->str, '0') && (parse->flags & NEGATIVE
		|| parse->flags & PLUS || (parse->flags & HASHTAG
		&& ft_strchr("xX", parse->specifier))))
	{
		while (parse->str[zero] && parse->str[zero] != '0')
			zero++;
		while (parse->str[i] && (parse->str[i] == '0' || parse->str[i] == ' '))
			i++;
		if (parse->flags & HASHTAG && ft_strchr("xX", parse->specifier))
			zero++;
		if (i > zero)
		{
			tmp = parse->str[i];
			parse->str[i] = parse->str[zero];
			parse->str[zero] = tmp;
		}
	}
}
