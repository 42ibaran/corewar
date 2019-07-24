/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 13:08:52 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"

typedef struct		s_word
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
	char			is_quote;
	char			is_command;
	struct s_word	*next;
}					t_word;

typedef struct		s_string
{
	int				nbr;
	char			*line;
	t_word			*word;
	t_word			*last_word;
	struct s_string	*next;
}					t_string;

/*
** asm_helpers.c
*/
void				error(char code);

/*
** asm_check.c
*/
t_string			*check_and_read(int ac, char **av);

/*
** asm_init.c
*/
t_string			*init_string(int nbr);
t_word				*init_word(char *line, int j, int i);

/*
** asm_debug.c
*/
void				print_strings(t_string *string);
void				print_definition(t_word *word);

/*
** asm_translator.c
*/
char				*translate(t_string *string);

#endif
