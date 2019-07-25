/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 13:07:54 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 10:16:19 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

// void	putchar_in_out(t_output *out, char c)
// {
// 	out->string[out->pos] = c;
// 	out->pos++;
// }

// void	magic(t_output *out)
// {
// 	unsigned int	magic_n;
// 	unsigned int	divider;

// 	divider = 0x1000000;
// 	magic_n = COREWAR_EXEC_MAGIC;
// 	while (divider != 0)
// 	{
// 		putchar_in_out(out, magic_n / divider);
// 		magic_n %= divider;
// 		divider /= 0x100;
// 	}
// }

void		code(t_champion *champ, t_string *string)
{
	champ = NULL;
	string = NULL;
}

t_output	*translate(t_string *string)
{
	t_output	*out;
	t_champion	*champ;
	t_word		*word;

	champ = init_champion();
	while (string)
	{
		word = string->word;
		while (word && word->is_space)
			word = word->next;
		//
		if (!word)
		{
			string = string->next;
			continue ;
		}
		//
		if (!ft_strcmp(word->str, NAME_CMD_STRING))
			name(champ, string);
		else if (!ft_strcmp(word->str, COMMENT_CMD_STRING))
			comment(champ, string);
		else if (champ->name_size != -1 && champ->comment_size != -1)
			code(champ, string);
		else if (word && !word->is_quote)
			error(ERR_COMMON);
			//translator_error(champ, string);
		string = string->next;
	}
	ft_printf("%s\n", champ->name);
	ft_printf("%s\n", champ->comment);
	return (out = NULL);
}
