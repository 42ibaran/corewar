/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 18:00:07 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "libft.h"
# include "op.h"

/*
** ==================== Error codes ===========================================
*/

# define ERR_MEMORY 1
# define ERR_COMMON 0
# define ERR_USAGE -1
# define ERR_READ -2
# define ERR_WRITE -3
# define ERR_MAGIC -4
# define ERR_END -5

# define ERR_INV_REGISTER -1
# define ERR_TOO_MANY_ARGS -2
# define ERR_NOT_ENOUGH_ARGS -3
# define ERR_WRONG_ARG_TYPE -4
# define ERR_UNKNOWN_LABEL -5
# define ERR_NO_NAME_OR_COMMENT -6
# define ERR_NAME_EXISTS -7
# define ERR_COMMENT_EXISTS -8
# define ERR_NAME_TOO_LONG -9
# define ERR_COMMENT_TOO_LONG -10
# define ERR_UNKMOWN_OPERATION -11
# define ERR_UNEXPECTED_TOKEN -12
# define ERR_INVALID_ARG -13
# define ERR_SEPARATOR -14

/*
** ==================== Constant definition ===================================
*/

# define MAX_ARG_VAL_ABS 0xffffff0000000000

/*
** ==================== Global variable line of input =========================
*/
int							g_input_l;
/*
** ==================== Word structure ========================================
*/
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
/*
** ==================== String structure ======================================
*/
typedef struct				s_string
{
	int						nbr;
	char					*line;
	t_word					*word;
	t_word					*last_word;
	struct s_string			*next;
}							t_string;
/*
** ==================== Operation structure ===================================
**
** arg_type:
** -1 = empty
** 0 = register
** 1 = direct
** 2 = indirect
*/
typedef struct				s_operation
{
	char					oper_code;
	int						arg_type_code;
	int						line_nbr;
	char					*arg_str[3];
	unsigned int			arg_value[3];
	char					arg_type[3];
	char					arg_size[3];
	char					arg_nbr;
	int						length;
	unsigned char			*binary;
	struct s_operation		*next;
}							t_operation;
/*
** ==================== Instruction structure =================================
*/
typedef struct				s_instruction
{
	char					*name;
	int						length;
	t_operation				*operation;
	t_operation				*last_operation;
	struct s_instruction	*next;
}							t_instruction;
/*
** ==================== Champion structure ====================================
*/
typedef struct				s_champion
{
	char					name[PROG_NAME_LENGTH + 1];
	int						name_size;
	char					comment[COMMENT_LENGTH + 1];
	int						comment_size;
}							t_champion;
/*
** ==================== Output structure ======================================
*/
typedef struct				s_output
{
	t_champion				*champ;
	t_instruction			*instr;
}							t_output;
/*
** ==================== Free structure ========================================
** Contains pointers to structures that must be feed in case of an error
** or at the end of the program execution. Global variable to easily access
** the data from any point of program
*/
typedef struct				s_free
{
	t_string				*first_string;
	t_instruction			*first_instr;
	t_output				*first_out;
}							t_free;

t_free						g_free;
/*
** ==================== Return value typedef ==================================
** definition of type that is returned by functions:
** get_check_operation() and get_f_arr()
** that return pointers to functions
*/
typedef void				(*t_check_oper)(t_operation*, t_word*);
typedef char				(*t_check_arg)(t_word*);

/*
*******************************************************************************
*******************************************************************************
** ============================================================================
** ==================== Functions prototypes ==================================
** ============================================================================
*******************************************************************************
*******************************************************************************
** ==================== asm_errors.c ==========================================
*/
void						error(char code);
void						lex_error(char code, char *instr);
/*
** ==================== asm_check.c ===========================================
*/
t_string					*read_and_save(int ac, char **av);
/*
** ==================== asm_define_word.c =====================================
*/
t_word						*allocate_and_define(char *line, int i, int j,
							char quote);
/*
** ==================== asm_init.c ============================================
*/
t_string					*init_string(int nbr);
t_word						*init_word(char *line, int j, int i);
t_output					*init_output(void);
t_champion					*init_champion(void);
t_instruction				*init_instruction(char *name);
t_operation					*init_operation(char *name);
/*
** ==================== asm_debug.c ===========================================
*/
void						print_strings(t_string *string);
void						print_definition(t_word *word);
void						print_all_instuctions(t_instruction *instr);
/*
** ==================== asm_new_struct.c ======================================
*/
void						new_string(t_string **string, t_string
							**next_string, int nbr);
void						new_instruction(t_instruction **instr,
							t_instruction **next_instr, char *str);
void						new_operation(t_instruction **instr, t_instruction
							**next_instr, char *str);
void						init_globals(void);
/*
** ==================== asm_translator.c ======================================
*/
t_output					*translate(t_string *string);
void						putchar_in_out(t_output *out, char c);
char						oper_name_to_code(char *name);
/*
** ==================== asm_write_file.c ======================================
*/
void						write_into_file(t_output *out, char *name);
/*
** ==================== asm_put_name.c ========================================
*/
void						name(t_champion *champ, t_string *string);
/*
** ==================== asm_put_comment.c =====================================
*/
void						comment(t_champion *champ, t_string *string);
/*
** ==================== asm_put_code.c ========================================
*/
void						code(t_instruction *instr);
/*
** ==================== asm_prepare_operations.c ==============================
*/
t_instruction				*prepare_operations(t_string *string,
							t_instruction *instr, t_instruction *next_instr);
void						fill_arg_type(t_operation *oper, t_word *word,
							char arg_nbr);
/*
** ==================== asm_get_operation_parameters.c ========================
*/
t_check_oper				get_check_operation(char code);
char						get_dir_size(char code);
char						get_is_type_code_required(char code);
char						get_oper_code(char *name);
/*
** ==================== asm_check_operations.c ================================
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
** ==================== asm_word_is_what.c ====================================
*/
char						w_is_reg(t_word *word);
char						w_is_dir(t_word *word);
char						w_is_indir(t_word *word);
/*
** ==================== asm_check_arg.c =======================================
*/
void						check_arg(t_word **word, t_check_arg *f,
							char *oper);
void						check_sep(t_word **word, char *oper);
void						check_null(t_word **word, char *oper);
/*
** ==================== asm_get_f_arr.c =======================================
*/
t_check_arg					*get_f_arr(int code);
/*
** ==================== asm_definition.c ======================================
*/
void						word_is_space(char *line, int j, t_word *word);
void						word_is_direct(char *line, int j, t_word *word);
void						word_is_indirect(t_word *word);
void						word_is_label(char *line, int j, t_word *word);
void						word_is_separator(char *line, int j, t_word *word);
void						word_is_quote(t_word *word, char quote);
void						word_is_operation(char *line, int j, int i,
							t_word *word);
void						word_is_register(char *line, int j, int i,
							t_word *word);
void						word_is_command(char *line, int j, int i,
							t_word *word);
void						word_is_instruction(char *line, int i,
							t_word *word);
/*
** ==================== asm_get_label_distance.c ==============================
*/
int							get_label_distance(t_operation *oper,
							t_instruction *instr, char *name);
/*
** ==================== asm_process_negative_arg_val.c ========================
*/
int							process_negative_val(__int128_t val, char arg_size);
/*
** ==================== asm_free.c ============================================
*/
void						f_free(void);
/*
** ============================================================================
*/

#endif
