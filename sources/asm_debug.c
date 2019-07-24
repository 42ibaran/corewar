/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:57:20 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 12:54:01 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_strings(t_string *string)
{
	t_word		*word;

	while (string)
	{
		ft_putnbr(string->nbr);
		word = string->word;
		while (word)
		{
			if (!word->is_space) //&&!word->is_separator)
			{
				ft_printf("%s ", word->str);
				print_definition(word);
			}
			word = word->next;
		}
		ft_printf("\n");
		string = string->next;
	}
}

void		print_definition(t_word *word)
{
	if (!word)
		return ;
	if (word->is_label)
		ft_printf(" label ");
	if (word->is_instruction)
		ft_printf(" instruction ");
	if (word->is_register)
		ft_printf(" register ");
	if (word->is_separator)
		ft_printf(" separator ");
	if (word->is_direct)
		ft_printf(" direct ");
	if (word->is_name)
		ft_printf(" name ");
	if (word->is_comment)
		ft_printf(" comment ");
	if (word->is_command)
		ft_printf(" command ");
	if (word->is_quote)
		ft_printf(" quote ");
}
