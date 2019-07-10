/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_uoxx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:03:16 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:43:30 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_add_bullshit(char *string, t_specifier *specifier,
				unsigned long long number)
{
	if (CONVERSION == 'o' && (number != 0 || PRECISION == 0))
	{
		string = ft_strnjoin(ft_dupexit("0"), string, 1, g_str_len);
		g_str_len++;
	}
	if ((CONVERSION == 'x' || CONVERSION == 'X') && number != 0)
	{
		string = ft_strnjoin(ft_dupexit("0X"), string, 2, g_str_len);
		g_str_len += 2;
	}
	return (string);
}

char			*ft_wi_pr_for_uuoxxb_2(char *string, t_specifier *specifier,
				unsigned long long number, char width_filler)
{
	if (WIDTH > g_str_len)
	{
		if (ft_strchr(FLAGS, '-') == NULL)
			string = ft_strnjoin(ft_nctoaexit(width_filler, WIDTH -
			g_str_len), string, WIDTH - g_str_len, g_str_len);
		else
			string = ft_strnjoin(string, ft_nctoaexit(width_filler, WIDTH -
			g_str_len), g_str_len, WIDTH - g_str_len);
		g_str_len = WIDTH;
	}
	if (ft_strchr(FLAGS, '#') != NULL && ft_strchr(FLAGS, '0') != NULL)
		string = ft_add_bullshit(string, specifier, number);
	return (string);
}

char			*ft_wi_pr_for_uuoxxb(char *string, t_specifier *specifier,
				unsigned long long number)
{
	char	width_filler;

	width_filler = ' ';
	if (ft_strchr(FLAGS, '0') != NULL && ft_strchr(FLAGS, '-') == NULL &&
	PRECISION == -1)
		width_filler = '0';
	if (ft_strchr(FLAGS, '#') != NULL && ft_strchr(FLAGS, '0') != NULL)
	{
		if (CONVERSION == 'o')
			WIDTH -= 1;
		if (CONVERSION == 'x' || CONVERSION == 'X')
			WIDTH -= 2;
	}
	if (ft_strchr(FLAGS, '#') != NULL && ft_strchr(FLAGS, '0') == NULL)
		string = ft_add_bullshit(string, specifier, number);
	string = ft_wi_pr_for_uuoxxb_2(string, specifier, number, width_filler);
	if (CONVERSION == 'x')
		string = ft_strtolower(string);
	return (string);
}

unsigned short	ft_base(char conversion)
{
	if (conversion == 'u' || conversion == 'U')
		return (10);
	if (conversion == 'o')
		return (8);
	if (conversion == 'x' || conversion == 'X')
		return (16);
	if (conversion == 'b')
		return (2);
	return (0);
}

char			*none_uuoxxb(void *po, t_specifier *specifier)
{
	char					*string;
	unsigned long long		*number;

	number = po;
	if (*number == 0 && PRECISION == 0)
		string = ft_dupexit("");
	else if (!(string = ft_itoa_base(*number, ft_base(CONVERSION))))
		exit(EXIT_FAILURE);
	g_str_len = ft_strlen(string);
	if (PRECISION > g_str_len)
	{
		string = ft_strnjoin(ft_nctoaexit('0', PRECISION - g_str_len), string,
		PRECISION - g_str_len, g_str_len);
		g_str_len = PRECISION;
	}
	string = ft_wi_pr_for_uuoxxb(string, specifier, *number);
	free(po);
	return (string);
}
