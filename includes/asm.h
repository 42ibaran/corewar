/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 19:37:23 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "op.h"

# define BUFF_OUT_STR 0xfff

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

typedef struct		s_output
{
	char			*string;
	int				pos;
	int				size;
}					t_output;

typedef struct		s_champion
{
	char			name[PROG_NAME_LENGTH + 1];
	int				name_size;
	char			comment[COMMENT_LENGTH + 1];
	int				comment_size;
	char			*code;
	int				code_size;
}					t_champion;

/*
** asm_helpers.c
*/
void				error(char code);

/*
** asm_check.c
*/
t_string			*read_and_save(int ac, char **av);

/*
** asm_init.c
*/
t_string			*init_string(int nbr);
t_word				*init_word(char *line, int j, int i);
t_output			*init_output(void);
t_champion			*init_champion(void);

/*
** asm_debug.c
*/
void				print_strings(t_string *string);
void				print_definition(t_word *word);

/*
** asm_translator.c
*/
t_output			*translate(t_string *string);
void				putchar_in_out(t_output *out, char c);

/*
** asm_write_file.c
*/
void				write_into_file(t_output *out, char *name);

/*
** asm_put_name.c
*/
//void				name(t_output *out, t_string *string);
void				name(t_champion *champ, t_string *string);

/*
** asm_put_comment.c
*/
//void				comment(t_output *out, t_string *string);
void				comment(t_champion *champ, t_string *string);

#endif
