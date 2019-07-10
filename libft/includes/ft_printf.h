/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:34:24 by ibaran            #+#    #+#             */
/*   Updated: 2019/03/13 16:11:43 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <libc.h>
# include <stdarg.h>
# include "libft.h"

# define FLAGS specifier->flags
# define WIDTH specifier->width
# define PRECISION specifier->precision
# define LENGTH specifier->length
# define CONVERSION specifier->conversion

# define RED "\033[38;1;31m"
# define DARK_RED "\033[38;0;31m"
# define GREEN "\033[38;1;32m"
# define DARK_GREEN "\033[38;0;32m"
# define YELLOW "\033[38;1;33m"
# define DARK_YELLOW "\033[38;0;33m"
# define BLUE "\033[38;1;34m"
# define DARK_BLUE "\033[38;0;34m"
# define MAGENTA "\033[38;1;35m"
# define DARK_MAGENTA "\033[38;0;35m"
# define CYAN "\033[38;1;36m"
# define DARK_CYAN "\033[38;0;36m"
# define EOC "\033[38;0;00m"

int				g_res_len;
int				g_str_len;

typedef struct	s_specifier
{
	char		*flags;
	int			width;
	int			precision;
	char		*length;
	char		conversion;
}				t_specifier;

typedef struct	s_functions
{
	char		*(*funs[8])(void*, t_specifier*);
	char		*conversions[8];
}				t_functions;

int				ft_printf(const char *format, ...);

/*
** FT_IMPORTANTS.C
*/
char			*ft_strnjoin(char *s1, char *s2, size_t n1, size_t n2);
int				get_specif(const char *format, t_specifier *specifier,
				unsigned int *j);
void			ft_reset_specifier(t_specifier *specifier,
				unsigned short first);
int				ft_final(char *result, va_list *ap, t_specifier *specifier);
/*
** FT_GETTING_ARGUMENT.C
*/
char			*ft_get_argument(va_list *ap, char *result,
				t_specifier *specifier);
/*
** FT_FILLING.C
*/
void			ft_fill_flags(const char *format, unsigned int *i,
				t_specifier *specifier);
void			ft_fill_width(const char *format, unsigned int *i,
				t_specifier *specifier);
void			ft_fill_precision(const char *format, unsigned int *i,
				t_specifier *specifier);
void			ft_fill_length(const char *format, unsigned int *i,
				t_specifier *specifier);
/*
** FOR_DI.C
*/
char			*none_di(void *po, t_specifier *specifier);
/*
** FOR_UOXX.C
*/
char			*none_uuoxxb(void *po, t_specifier *specifier);
/*
** FT_CSPPERCENT.C
*/
char			*none_c(void *po, t_specifier *specifier);
char			*none_s(void *po, t_specifier *specifier);
char			*none_p(void *po, t_specifier *specifier);
char			*none_percent(void *po, t_specifier *specifier);
/*
** FT_F.C
*/
char			*none_f(void *po, t_specifier *specifier);
char			*none_n(void *po, t_specifier *specifier);
/*
** FT_STRNCPY_ZERO.C
*/
char			*ft_strncpy_zero(char *dest, const char *src, size_t n);
/*
** FT_ARGUMENT_VALUE.C
*/
void			*arg_value(int i, va_list *ap, t_specifier *specifier);
/*
** FT_DUPEXIT.C
*/
char			*ft_dupexit(const char *src);
char			*ft_ctoaexit(char c);
char			*ft_strndupexit(const char *src, size_t n);
char			*ft_nctoaexit(char c, size_t n);
/*
** FT_COLOR.c
*/
char			*ft_set_color(char *result, const char *format,
				unsigned int *j);

#endif
