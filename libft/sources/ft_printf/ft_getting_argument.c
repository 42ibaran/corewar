/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getting_argument.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:44:09 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 10:18:25 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_functions			*ft_fill_table(void)
{
	t_functions		*out;

	out = (t_functions*)malloc(sizeof(t_functions));
	out->funs[0] = &none_di;
	out->funs[1] = &none_uuoxxb;
	out->funs[2] = &none_f;
	out->funs[3] = &none_c;
	out->funs[4] = &none_s;
	out->funs[5] = &none_p;
	out->funs[6] = &none_percent;
	out->funs[7] = &none_n;
	out->conversions[0] = ft_dupexit("di");
	out->conversions[1] = ft_dupexit("uUoxXb");
	out->conversions[2] = ft_dupexit("fF");
	out->conversions[3] = ft_dupexit("c");
	out->conversions[4] = ft_dupexit("s");
	out->conversions[5] = ft_dupexit("p");
	out->conversions[6] = ft_dupexit("%");
	out->conversions[7] = ft_dupexit("n");
	return (out);
}

void				ft_free_table(t_functions *pointer)
{
	int		i;

	i = -1;
	while (++i < 8)
		free(pointer->conversions[i]);
	free(pointer);
}

char				*ft_get_argument(va_list *ap, char *result,
					t_specifier *specifier)
{
	int				i;
	int				j;
	char			*string;
	t_functions		*functions;

	functions = ft_fill_table();
	i = 0;
	j = 0;
	g_str_len = 0;
	while (i < 8 && ft_strchr(functions->conversions[i], CONVERSION) == NULL)
		i++;
	if (i == 8)
		return (result);
	string = functions->funs[i](arg_value(i, ap, specifier), specifier);
	result = ft_strnjoin(result, string, g_res_len, g_str_len);
	g_res_len += g_str_len;
	ft_free_table(functions);
	return (result);
}
