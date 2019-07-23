/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/17 15:00:34 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"

typedef struct		s_lexer
{
	char			*str;
	char			is_label;
	char			is_instruction;
	char			is_register;
	char			is_separator;
	char			is_direct;
	char			is_name;
	char			is_comment;
	char			is_space;
	char			is_command;
	struct s_lexer	*next;
}					t_lexer;

typedef struct		s_string
{
	char			*line;
	t_lexer			*word;
	t_lexer			*last_word;
	struct s_string	*next;
}					t_string;

/*
** asm_helpers.c
*/
void				error(char code);

/*
** asm_check.c
*/
void				check_and_read(int ac, char **av);

/*
** asm_init.c
*/
t_string			*init_string(void);
t_lexer				*init_lexer(char *line, int j, int i);

/*
** asm_debug.c
*/
void				print_strings(t_string *string);
void				print_definition(t_lexer *lexer);

#endif
