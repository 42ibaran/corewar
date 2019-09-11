/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:48:41 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:49:22 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_type_char(va_list args, t_parse *parse)
{
	char	c;
	char	*str;

	c = (char)va_arg(args, int);
	if (c == '\0')
	{
		ft_putchar_fd(c, parse->fd);
		parse->len++;
	}
	else
	{
		if (!(str = ft_strnew(1)))
			return ;
		str[0] = c;
		if (!(parse->str = ft_strdup(str)))
			return ;
		ft_strdel(&str);
	}
}

void		ft_type_str(va_list args, t_parse *parse)
{
	char	*s;

	s = va_arg(args, char*);
	if (s == 0)
	{
		if (!(parse->str = ft_strdup("(null)")))
			return ;
	}
	else
	{
		if (!(parse->str = ft_strdup(s)))
			return ;
	}
}

void		ft_type_ptr(va_list args, t_parse *parse)
{
	unsigned long	p;
	char			*str;

	p = (unsigned long)va_arg(args, void*);
	if (!(str = ft_lltoa_base(p, 16)))
		return ;
	if (!(parse->str = ft_strjoin("0x", str)))
		return ;
	ft_strdel(&str);
}
