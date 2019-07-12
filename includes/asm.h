/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:58:50 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/12 15:33:26 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

typedef struct	s_lexer
{
	char		*str;
	char		is_label;
	char		is_instruction;
	char		is_register;
	char		is_separator;
	char		is_direct;
	char		is_name;
	char		is_comment;
	char		is_space;
	char		is_command;
}				t_lexer;

/*
** asm_helpers.c
*/
void			error(char code);

/*
** asm_check.c
*/
void			check_and_read(int ac, char **av);


#endif
