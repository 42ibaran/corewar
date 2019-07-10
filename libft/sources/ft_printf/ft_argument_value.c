/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argument_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 10:17:20 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:48:08 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			*arg_is_signed_int(va_list *ap, t_specifier *specifier)
{
	long long	*number;

	if (!(number = (long long*)malloc(sizeof(long long))))
		exit(EXIT_FAILURE);
	if (ft_strcmp(LENGTH, "h") == 0)
		*number = (short)va_arg(*ap, long long);
	else if (ft_strcmp(LENGTH, "hh") == 0)
		*number = (signed char)va_arg(*ap, long long);
	else if (ft_strcmp(LENGTH, "l") == 0)
		*number = (long)va_arg(*ap, long long);
	else if (ft_strcmp(LENGTH, "ll") == 0 || ft_strcmp(LENGTH, "j") == 0)
		*number = va_arg(*ap, long long);
	else if (ft_strcmp(LENGTH, "z") == 0)
		*number = (size_t)va_arg(*ap, long long);
	else
		*number = (int)va_arg(*ap, long long);
	return (number);
}

unsigned long long	*arg_is_unsigned_int(va_list *ap, t_specifier *specifier)
{
	unsigned long long		*number;

	if (!(number = (unsigned long long*)malloc(sizeof(unsigned long long))))
		exit(EXIT_FAILURE);
	if (ft_strcmp(LENGTH, "h") == 0 && CONVERSION != 'U')
		*number = (unsigned short)va_arg(*ap, unsigned long long);
	else if (ft_strcmp(LENGTH, "hh") == 0)
		*number = (unsigned char)va_arg(*ap, unsigned long long);
	else if (ft_strcmp(LENGTH, "l") == 0 || CONVERSION == 'U')
		*number = (unsigned long)va_arg(*ap, unsigned long long);
	else if (ft_strcmp(LENGTH, "ll") == 0 || ft_strcmp(LENGTH, "j") == 0)
		*number = va_arg(*ap, unsigned long long);
	else if (ft_strcmp(LENGTH, "z") == 0)
		*number = (size_t)va_arg(*ap, long long);
	else
		*number = (unsigned int)va_arg(*ap, unsigned long long);
	return (number);
}

long double			*arg_is_float(va_list *ap, t_specifier *specifier)
{
	long double		*number;

	if (!(number = (long double*)malloc(sizeof(long double))))
		exit(EXIT_FAILURE);
	if (ft_strcmp(LENGTH, "L") == 0)
		*number = va_arg(*ap, long double);
	else
		*number = va_arg(*ap, double);
	return (number);
}

void				*arg_value(int i, va_list *ap, t_specifier *specifier)
{
	if (i == 0 || i == 3)
		return (arg_is_signed_int(ap, specifier));
	if (i == 1)
		return (arg_is_unsigned_int(ap, specifier));
	if (i == 2)
		return (arg_is_float(ap, specifier));
	if (i == 4 || i == 5 || i == 7)
	{
		if (CONVERSION == 's')
			return (va_arg(*ap, char*));
		else if (CONVERSION == 'p')
			return (va_arg(*ap, void*));
		else
			*va_arg(*ap, int*) = g_res_len;
	}
	return (NULL);
}
