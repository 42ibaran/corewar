/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:53:29 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 10:53:49 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	unsigned int	i;
	unsigned int	j;
	va_list			ap;
	char			*result;
	t_specifier		specifier;

	result = ft_dupexit("");
	g_res_len = 0;
	va_start(ap, format);
	j = 0;
	ft_reset_specifier(&specifier, 0);
	while (format[j] != '\0')
	{
		i = j;
		ft_reset_specifier(&specifier, 1);
		while (format[j] != '%' && format[j] != '{' && format[j] != '\0')
			j++;
		result = ft_strnjoin(result, ft_dupexit(format + i), g_res_len, j - i);
		g_res_len += j - i;
		if (format[j] == '%' && get_specif(format + j + 1, &specifier, &j) == 0)
			result = ft_get_argument(&ap, result, &specifier);
		else if (format[j] == '{')
			result = ft_set_color(result, format + j + 1, &j);
	}
	return (ft_final(result, &ap, &specifier));
}
