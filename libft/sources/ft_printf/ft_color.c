/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:52:30 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:37:02 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_color_string_next(char *str)
{
	char	*out;

	if (ft_strcmp(str, "magenta") == 0)
		out = ft_dupexit(MAGENTA);
	else if (ft_strcmp(str, "dark_magenta") == 0)
		out = ft_dupexit(DARK_MAGENTA);
	else if (ft_strcmp(str, "cyan") == 0)
		out = ft_dupexit(CYAN);
	else if (ft_strcmp(str, "dark_cyan") == 0)
		out = ft_dupexit(DARK_CYAN);
	else if (ft_strcmp(str, "eoc") == 0)
		out = ft_dupexit(EOC);
	else
		out = NULL;
	free(str);
	return (out);
}

char		*ft_color_string(char *str)
{
	char	*out;

	if (ft_strcmp(str, "red") == 0)
		out = ft_dupexit(RED);
	else if (ft_strcmp(str, "dark_red") == 0)
		out = ft_dupexit(DARK_RED);
	else if (ft_strcmp(str, "green") == 0)
		out = ft_dupexit(GREEN);
	else if (ft_strcmp(str, "dark_green") == 0)
		out = ft_dupexit(DARK_GREEN);
	else if (ft_strcmp(str, "yellow") == 0)
		out = ft_dupexit(YELLOW);
	else if (ft_strcmp(str, "dark_yellow") == 0)
		out = ft_dupexit(DARK_YELLOW);
	else if (ft_strcmp(str, "blue") == 0)
		out = ft_dupexit(BLUE);
	else if (ft_strcmp(str, "dark_blue") == 0)
		out = ft_dupexit(DARK_BLUE);
	else
		return (ft_color_string_next(str));
	return (out);
}

char		*ft_set_color(char *result, const char *format, unsigned int *j)
{
	int		i;
	char	*tmp;

	i = 0;
	while (format[i] != '\0' && format[i] != '}')
		i++;
	if (format[i] != '\0')
		*j += i + 2;
	else
	{
		*j = *j - 1;
		return (result);
	}
	if ((tmp = ft_color_string(ft_strndupexit(format, i))) != NULL)
	{
		result = ft_strnjoin(result, tmp, g_res_len, 10);
		g_res_len += 10;
	}
	else
	{
		result = ft_strnjoin(result, ft_ctoaexit('{'), g_res_len, 1);
		g_res_len++;
		*j -= (i + 1);
	}
	return (result);
}
