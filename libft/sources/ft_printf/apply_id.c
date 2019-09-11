/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 14:50:36 by ephe              #+#    #+#             */
/*   Updated: 2019/09/06 13:19:09 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_null_precision(t_parse *parse)
{
	char	c;
	int		i;

	i = 0;
	if (parse->specifier == 's' && parse->precision == 0)
		ft_strdel(&parse->str);
	else if (ft_strchr("diouxX", parse->specifier) && parse->precision == 0
		&& parse->zero && !(parse->specifier == 'o' && parse->flags & HASHTAG))
	{
		c = (!parse->width) ? '\0' : ' ';
		while (parse->str[i])
		{
			if (parse->str[i] == '0')
				parse->str[i] = c;
			i++;
		}
	}
}

static void	ft_precision(t_parse *parse, char *str, int len)
{
	if (ft_strchr("diouxXf", parse->specifier) && len < parse->precision)
	{
		len = parse->precision - len;
		if (!(str = ft_strnew(len)))
			return ;
		ft_memset(str, '0', len);
		if (parse->specifier == 'f')
		{
			if (!(parse->str = ft_strjoinfree(parse->str, str, 1)))
				return ;
			ft_strdel(&str);
		}
		else
		{
			if (!(str = ft_strjoinfree(str, parse->str, 1)))
				return ;
			ft_strdel(&parse->str);
			parse->str = str;
		}
	}
}

void		ft_apply_precision(t_parse *parse, int len)
{
	if (!parse->str || parse->precision == -1)
		return ;
	if (parse->specifier == 'f')
	{
		while (parse->str[len] && parse->str[len] != '.')
			len++;
		len = ft_strlen(parse->str + len) - (parse->str[len] == '.');
	}
	else if (ft_strchr("sdiouxX", parse->specifier))
	{
		len = ft_strlen(parse->str);
		if (parse->flags & NEGATIVE)
			len--;
	}
	ft_precision(parse, 0, len);
	if (parse->specifier == 's' && len > parse->precision)
	{
		len = parse->precision - 1;
		while (parse->str[len++])
			parse->str[len] = '\0';
	}
	ft_null_precision(parse);
}

void		ft_apply_width(t_parse *parse, char *str, int len)
{
	if (!parse->str || !parse->width)
		return ;
	len = ft_strlen(parse->str);
	if (len < parse->width)
	{
		if (!(str = ft_strnew(parse->width - len)))
			return ;
		ft_memset(str, (parse->flags & ZERO) && ((parse->precision == -1
			&& parse->specifier != 'f') || (parse->precision == 0
			&& parse->specifier == 'f')) ? '0' : ' ', parse->width - len);
		if (parse->flags & MINUS)
		{
			if (!(parse->str = ft_strjoinfree(parse->str, str, 1)))
				return ;
			ft_strdel(&str);
		}
		else
		{
			if (!(str = ft_strjoinfree(str, parse->str, 1)))
				return ;
			ft_strdel(&parse->str);
			parse->str = str;
		}
	}
}
