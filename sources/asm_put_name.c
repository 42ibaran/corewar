/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:21:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/25 13:27:42 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

void	name(t_champion *champ, t_string *string)
{
	t_word		*word;

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
		//if (champ->name_size != -1)
		//	ft_strcat(champ->name, "\n");
		champ->name_size += (champ->name_size == -1 ?
				ft_strlen(word->str) + 1 : ft_strlen(word->str));
		if (champ->name_size > PROG_NAME_LENGTH)
			error(ERR_COMMON); //change error code // name too long
		ft_strcat(champ->name, word->str);
		string = string->next;
	}
}
