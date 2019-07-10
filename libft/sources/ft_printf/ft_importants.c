/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_importants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:00:41 by ibaran            #+#    #+#             */
/*   Updated: 2019/02/08 11:00:46 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_strnjoin(char *s1, char *s2, size_t n1, size_t n2)
{
	char			*result;

	if (!(result = (char*)malloc(sizeof(char) * (n1 + n2 + 1))))
		exit(EXIT_FAILURE);
	ft_strncpy_zero(result, s1, n1);
	ft_strncpy_zero(result + n1, s2, n2);
	free(s1);
	free(s2);
	return (result);
}

void			ft_free_two_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int				get_specif(const char *format, t_specifier *specifier,
				unsigned int *j)
{
	unsigned int	i;
	char			*possible_conversions;
	char			*possible_flags;

	possible_conversions = ft_dupexit("diuUoxXbfFcspn%");
	possible_flags = ft_dupexit("-+ #0123456789.hlLjz");
	i = 0;
	while (format[i] != '\0' && ft_strchr(possible_flags, format[i]) != NULL &&
			ft_strchr(possible_conversions, format[i]) == NULL)
		i++;
	if (ft_strchr(possible_conversions, format[i]) == NULL || format[i] == '\0')
	{
		*j = *j + i + 1;
		ft_free_two_strings(possible_conversions, possible_flags);
		return (-2);
	}
	CONVERSION = format[i];
	i = 0;
	ft_fill_flags(format, &i, specifier);
	ft_fill_width(format, &i, specifier);
	ft_fill_precision(format, &i, specifier);
	ft_fill_length(format, &i, specifier);
	*j += (ft_strchr(format, CONVERSION) - format) + 2;
	ft_free_two_strings(possible_conversions, possible_flags);
	return (0);
}

void			ft_reset_specifier(t_specifier *specifier, unsigned short first)
{
	if (first == 2 || first == 1)
		ft_free_two_strings(FLAGS, LENGTH);
	if (first == 0 || first == 1)
	{
		FLAGS = ft_dupexit("");
		WIDTH = -1;
		PRECISION = -1;
		LENGTH = ft_dupexit("");
		CONVERSION = '?';
	}
}

int				ft_final(char *result, va_list *ap, t_specifier *specifier)
{
	write(1, result, g_res_len);
	va_end(*ap);
	ft_reset_specifier(specifier, 2);
	free(result);
	return (g_res_len);
}
