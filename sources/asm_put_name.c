/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:21:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:09 by ibaran           ###   ########.fr       */
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
			if (champ->name_size != -1 && !word->is_space && !word->is_quote)
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
		string = string->next;
	}
}
