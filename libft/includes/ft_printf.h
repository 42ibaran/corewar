/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:34:24 by ibaran            #+#    #+#             */
/*   Updated: 2019/09/06 13:13:33 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <libc.h>
# include <stdarg.h>
# include "libft.h"

# define HASHTAG 1
# define ZERO 2
# define MINUS 4
# define PLUS 8
# define SPACE 16
# define NEGATIVE 32

typedef union		u_dparts
{
	struct			s_parts
	{
		uint64_t	frac : 52;
		uint16_t	exp : 11;
		uint8_t		sign : 1;
	}				p;
	double			d;
}					t_dparts;

typedef struct		s_parse
{
	char			*str;
	char			flags;
	int				width;
	int				precision;
	char			sub_specifier;
	char			specifier;
	int				len;
	int				zero;
	int				fd;
}					t_parse;

typedef struct		s_type
{
	char			c;
	void			(*f)(va_list list, t_parse *parse);
}					t_type;

int					ft_printf(const char *format, ...);

int					ft_flag_id(int i, t_parse *parse, const char *format);
int					ft_width_id(int i, va_list args, t_parse *parse,
					const char *format);
int					ft_precision_id(int i, va_list args, t_parse *parse,
					const char *format);
void				ft_apply_flags(t_parse *parse, char *str);
void				ft_apply_sign(t_parse *parse);
void				ft_apply_width(t_parse *parse, char *str, int len);
void				ft_apply_precision(t_parse *parse, int len);
int					ft_sub_specifier_id(int i, t_parse *parse,
					const char *format);
void				ft_specifier_id(int i, va_list args, t_parse *parse,
					const char *format);
void				ft_type_char(va_list args, t_parse *parse);
void				ft_type_str(va_list args, t_parse *parse);
void				ft_type_ptr(va_list args, t_parse *parse);
void				ft_type_int(va_list args, t_parse *parse);
void				ft_type_un_oct(va_list args, t_parse *parse);
void				ft_type_un_int(va_list args, t_parse *parse);
void				ft_type_un_hex(va_list args, t_parse *parse);
void				ft_type_un_hex_up(va_list args, t_parse *parse);
void				ft_type_float(va_list args, t_parse *parse);
void				ft_type_bin(va_list args, t_parse *parse);

#endif
