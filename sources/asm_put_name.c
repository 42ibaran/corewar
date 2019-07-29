/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:21:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/29 16:31:51 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	name(t_champion *champ, t_string *string)
{
	t_word		*word;

	if (champ->name_size != -1)
		lex_error(ERR_NAME_EXISTS, NULL);
	while (string)
	{
		word = string->word;
		while (word && !word->is_quote)
		{
			if (champ->name_size != -1 && !word->is_quote)
				return ;
			word = word->next;
		}
		if (!word)
			return ;
		champ->name_size += (champ->name_size == -1 ?
				ft_strlen(word->str) + 1 : ft_strlen(word->str));
		if (champ->name_size > PROG_NAME_LENGTH)
			lex_error(ERR_NAME_TOO_LONG, NULL);
		ft_strcat(champ->name, word->str);
		if (word->next && (g_input_l = string->nbr) != -1)
			lex_error(ERR_UNEXPECTED_TOKEN, word->next->str);
		string = string->next;
	}
}
