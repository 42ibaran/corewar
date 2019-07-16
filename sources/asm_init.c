/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:28:02 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/16 14:49:42 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_string	*init_string(void)
{
	t_string	*new_string;

	if (!(new_string = (t_string*)malloc(sizeof(t_string))))
		error(1);
	new_string->word = NULL;
	new_string->last_word = NULL;
	new_string->next = NULL;
	return (new_string);
}

t_lexer		*init_lexer(char *line, int j, int i)
{
	t_lexer		*lexer;
	
	if (!(lexer = (t_lexer*)malloc(sizeof(t_lexer))))
		error(1);
	if (!(lexer->str = ft_strndup(line + j, i - j + 1)))
		error(1);
	lexer->is_label = 0;
	lexer->is_instruction = 0;
	lexer->is_register = 0;
	lexer->is_separator = 0;
	lexer->is_direct = 0;
	lexer->is_name = 0;
	lexer->is_comment = 0;
	lexer->is_space = 0;
	lexer->is_command = 0;
	lexer->next = NULL;
	return (lexer);
}
