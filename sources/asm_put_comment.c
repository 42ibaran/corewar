/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_comment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:22:31 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 10:16:58 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

void	comment(t_champion *champ, t_string *string)
{
	t_word		*word;

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
		if (champ->comment_size != -1)
			ft_strcat(champ->comment, "\n");
		champ->comment_size += ft_strlen(word->str) + 1;
		if (champ->comment_size > COMMENT_LENGTH)
			error(ERR_COMMON); //change error code // comment too long
		ft_strcat(champ->comment, word->str);
		string = string->next;
	}
}
