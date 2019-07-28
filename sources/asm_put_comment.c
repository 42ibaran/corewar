/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:22:31 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/28 15:21:34 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	comment(t_champion *champ, t_string *string)
{
	t_word		*word;

	if (champ->comment_size != -1)
		lex_error(ERR_COMMENT_EXISTS, NULL);
	while (string)
	{
		word = string->word;
		while (word && !word->is_quote)
		{
			if (champ->comment_size != -1 && !word->is_space && !word->is_quote)
				return ;
			word = word->next;
		}
		if (!word)
			return ;
		champ->comment_size += (champ->comment_size == -1 ?
				ft_strlen(word->str) + 1 : ft_strlen(word->str));
		if (champ->comment_size > COMMENT_LENGTH)
			lex_error(ERR_COMMENT_TOO_LONG, NULL);
		ft_strcat(champ->comment, word->str);
		string = string->next;
	}
}
