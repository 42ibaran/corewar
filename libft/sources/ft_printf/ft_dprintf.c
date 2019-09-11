/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephe <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:33:14 by ephe              #+#    #+#             */
/*   Updated: 2019/03/26 16:49:14 by ephe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_identifiers(int i, va_list args, t_parse *parse,
const char *format)
{
	i = ft_flag_id(i, parse, format);
	i = ft_width_id(i, args, parse, format);
	i = ft_precision_id(i, args, parse, format);
	i = ft_sub_specifier_id(i, parse, format);
	if (format[i] == '%')
		if (!(parse->str = ft_strdup("%")))
			return (i);
	parse->specifier = 'c';
	ft_specifier_id(i, args, parse, format);
	ft_apply_precision(parse, 0);
	ft_apply_flags(parse, 0);
	ft_apply_width(parse, 0, 0);
	ft_apply_sign(parse);
	if (parse->str)
	{
		ft_putstr_fd(parse->str, parse->fd);
		parse->len = ft_strlen(parse->str);
		ft_strdel(&parse->str);
	}
	return (i);
}

static int	ft_parse(int fd, va_list args, t_parse *parse, const char *format)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_bzero(parse, sizeof(t_parse));
			parse->fd = fd;
			i++;
			i = ft_identifiers(i, args, parse, format);
			len += parse->len;
		}
		else
		{
			ft_putchar_fd(format[i], fd);
			len++;
		}
		i++;
	}
	return (len);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	int		len;
	t_parse	parse;
	va_list	args;

	va_start(args, format);
	if (format == NULL)
		return (0);
	len = ft_parse(fd, args, &parse, format);
	va_end(args);
	return (len);
}
