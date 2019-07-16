/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:57:20 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/16 14:58:00 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_strings(t_string *string)
{
	t_lexer		*lexer;

	while (string)
	{
		lexer = string->word;
		while (lexer)
		{
			if (!lexer->is_space && !lexer->is_separator)
			{
				ft_printf("%s ", lexer->str);
				print_definition(lexer);
			}
			lexer = lexer->next;
		}
		ft_printf("\n");
		string = string->next;
	}
}

void		print_definition(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->is_label)
		ft_printf(" label ");
	if (lexer->is_instruction)
		ft_printf(" instruction ");
	if (lexer->is_register)
		ft_printf(" register ");
	if (lexer->is_separator)
		ft_printf(" separator ");
	if (lexer->is_direct)
		ft_printf(" direct ");
	if (lexer->is_name)
		ft_printf(" name ");
	if (lexer->is_comment)
		ft_printf(" comment ");
	if (lexer->is_command)
		ft_printf(" command ");
}
