/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_di.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:59:21 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:42:48 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_ft_wi_pr_for_di_2(char *string, t_specifier *specifier)
{
	if (((ft_strchr(FLAGS, '0') == NULL) || (ft_strchr(FLAGS, '0') != NULL &&
	(ft_strchr(FLAGS, '-') != NULL || PRECISION >= 0))) && WIDTH > g_str_len)
	{
		if (ft_strchr(FLAGS, '-') == NULL)
			string = ft_strnjoin(ft_nctoaexit(' ', WIDTH - g_str_len), string,
			WIDTH - g_str_len, g_str_len);
		else
			string = ft_strnjoin(string, ft_nctoaexit(' ', WIDTH - g_str_len),
			g_str_len, WIDTH - g_str_len);
		g_str_len = WIDTH;
	}
	return (string);
}

char		*ft_wi_pr_for_di(char *string, t_specifier *specifier,
			long long number)
{
	int		i;

	g_str_len = ft_strlen(string);
	if (PRECISION > g_str_len)
	{
		string = ft_strnjoin(ft_nctoaexit('0', PRECISION - g_str_len), string,
		PRECISION - g_str_len, g_str_len);
		g_str_len = PRECISION;
	}
	if (ft_strchr(FLAGS, '0') != NULL && PRECISION < 0
	&& ft_strchr(FLAGS, '-') == NULL && WIDTH != -1)
	{
		i = ft_max((WIDTH - g_str_len - (ft_strchr(FLAGS, '+') != NULL ||
		ft_strchr(FLAGS, ' ') != NULL || number < 0)), 0);
		string = ft_strnjoin(ft_nctoaexit('0', i), string, i, g_str_len);
		g_str_len += i;
	}
	if (number < 0)
		string = ft_strnjoin(ft_ctoaexit('-'), string, 1, g_str_len);
	else if (ft_strchr(FLAGS, '+') != NULL)
		string = ft_strnjoin(ft_ctoaexit('+'), string, 1, g_str_len);
	else if (ft_strchr(FLAGS, ' ') != NULL)
		string = ft_strnjoin(ft_ctoaexit(' '), string, 1, g_str_len);
	g_str_len = ft_strlen(string);
	return (string = ft_ft_wi_pr_for_di_2(string, specifier));
}

char		*none_di(void *po, t_specifier *specifier)
{
	char		*string;
	char		*tmp;
	long long	*number;

	number = po;
	if (*number == 0 && PRECISION == 0)
		string = ft_dupexit("");
	else if (!(string = ft_itoa(*number)))
		exit(EXIT_FAILURE);
	if (string[0] == '-')
	{
		tmp = ft_dupexit(string + 1);
		free(string);
		string = tmp;
	}
	free(po);
	return (ft_wi_pr_for_di(string, specifier, *number));
}
