/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/27 14:27:38 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "op.h"

# define BUFF_OUT_STR 0xfff

typedef struct				s_word
{
	char					*str;
	char					is_instruction;
	char					is_operation;
	char					is_register;
	char					is_direct;
	char					is_indirect;
	char					is_label;
	char					is_separator;
	char					is_command;
	char					is_name;
	char					is_comment;
	char					is_space;
	char					is_quote;
	struct s_word			*next;
}							t_word;

typedef struct				s_string
{
	int						nbr;
	char					*line;
	t_word					*word;
	t_word					*last_word;
	struct s_string			*next;
}							t_string;

/*
** arg_type:
** -1 = empty or error (which basically can't happen)
** 0 = register
** 1 = direct
** 2 = indirect
*/
typedef struct				s_operation
{
	char					oper_code;
	int						arg_type_code;
	char					*arg_str[3];
	unsigned int			arg_value[3];
	char					arg_type[3];
	char					arg_size[3];
	char					arg_nbr;
	int						length;
	unsigned char			*binary;
	struct s_operation		*next;
}							t_operation;

typedef struct				s_instruction
{
	char					*name;
	int						length;
	t_operation				*operation;
	t_operation				*last_operation;
	struct s_instruction	*next;
	//struct s_instruction	*prev;
}							t_instruction;

typedef struct				s_champion
{
	char					name[PROG_NAME_LENGTH + 1];
	int						name_size;
	char					comment[COMMENT_LENGTH + 1];
	int						comment_size;
	char					*code;
	int						code_size;
}							t_champion;

typedef struct				s_output
{
	t_champion				*champ;
	t_instruction			*instr;
}							t_output;

typedef void (*t_check_oper)(t_operation*, t_word*);

/*
** asm_helpers.c
*/
void						error(char code);

/*
** asm_check.c
*/
t_string					*read_and_save(int ac, char **av);

/*
** asm_init.c
*/
t_string					*init_string(int nbr);
t_word						*init_word(char *line, int j, int i);
t_output					*init_output(void);
t_champion					*init_champion(void);
t_instruction				*init_instruction(char *name);
t_operation					*init_operation(char *name);

/*
** asm_debug.c
*/
void						print_strings(t_string *string);
void						print_definition(t_word *word);
void						print_all_instuctions(t_instruction *instr);

/*
**
*/
void						new_string(t_string **string, t_string
							**next_string, int nbr);
void						new_instruction(t_instruction **instr,
							t_instruction **next_instr, char *str);
void						new_operation(t_instruction **instr, t_instruction
							**next_instr, char *str);

/*
** asm_translator.c
*/
t_output					*translate(t_string *string);
void						putchar_in_out(t_output *out, char c);
char						oper_name_to_code(char *name);

/*
** asm_write_file.c
*/
void						write_into_file(t_output *out, char *name);

/*
** asm_put_name.c
*/
//void						name(t_output *out, t_string *string);
void						name(t_champion *champ, t_string *string);

/*
** asm_put_comment.c
*/
//void						comment(t_output *out, t_string *string);
void						comment(t_champion *champ, t_string *string);

/*
** asm_put_code.c
*/
t_instruction				*prepare_operations(t_string *string,
							t_instruction *instr, t_instruction *next_instr);
void						fill_arg_type(t_operation *oper, t_word *word,
							char arg_nbr);
void						code(t_instruction *instr);
/*
** asm_get_operation_parameters.c
*/
t_check_oper				get_check_operation(char code);
char						get_dir_size(char code);
char						get_is_type_code_required(char code);
char						get_oper_code(char *name);

/*
** asm_check_operations.c
*/
void						check_args_live(t_operation *oper, t_word *word);
void						check_args_ld(t_operation *oper, t_word *word);
void						check_args_st(t_operation *oper, t_word *word);
void						check_args_add(t_operation *oper, t_word *word);
void						check_args_sub(t_operation *oper, t_word *word);
void						check_args_and(t_operation *oper, t_word *word);
void						check_args_or(t_operation *oper, t_word *word);
void						check_args_xor(t_operation *oper, t_word *word);
void						check_args_zjmp(t_operation *oper, t_word *word);
void						check_args_ldi(t_operation *oper, t_word *word);
void						check_args_sti(t_operation *oper, t_word *word);
void						check_args_fork(t_operation *oper, t_word *word);
void						check_args_lld(t_operation *oper, t_word *word);
void						check_args_lldi(t_operation *oper, t_word *word);
void						check_args_lfork(t_operation *oper, t_word *word);
void						check_args_aff(t_operation *oper, t_word *word);

/*
** asm_definition.c
*/
void						word_is_space(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_quote(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_separator(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_command(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_label(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_instruction(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_operation(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_register(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_direct(char *line, int j, int i,
							t_word *word, char prev_quote);
void						word_is_indirect(char *line, int j, int i,
							t_word *word, char prev_quote);

/*
**
*/
int							get_label_distance(t_operation *oper,
							t_instruction *instr, char *name);

#endif
