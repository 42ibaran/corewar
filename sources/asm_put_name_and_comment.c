/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_put_name_and_comment.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:21:11 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/08 14:47:30 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		concat_name(t_champion *champ, t_string *string, t_word *word)
{
	champ->name_size += (champ->name_size == -1 ?
			ft_strlen(word->str) + 1 : ft_strlen(word->str));
	if (champ->name_size > PROG_NAME_LENGTH)
		lex_error(ERR_NAME_TOO_LONG, NULL);
	ft_strcat(champ->name, word->str);
	if (word->next && (g_input_l = string->nbr) != -1)
		lex_error(ERR_UNEXPECTED_TOKEN, word->next->str);
	if (!word->quote_is_open)
		return (1);
	return (0);
}

int				name(t_champion *champ, t_string *string)
{
	t_word		*word;
	int			to_return;

	to_return = -1;
	if (champ->name_size != -1)
		lex_error(ERR_NAME_EXISTS, NULL);
	while (string)
	{
		to_return++;
		word = string->word;
		while (word && !word->is_quote)
		{
			if (champ->name_size != -1 && !word->is_quote)
				return (to_return);
			word = word->next;
		}
		if (!word)
			return (to_return);
		if (concat_name(champ, string, word) == 1)
			return (to_return);
		string = string->next;
	}
	return (to_return);
}

static char		concat_comment(t_champion *champ, t_string *string,
				t_word *word)
{
	champ->comment_size += (champ->comment_size == -1 ?
			ft_strlen(word->str) + 1 : ft_strlen(word->str));
	if (champ->comment_size > COMMENT_LENGTH)
		lex_error(ERR_COMMENT_TOO_LONG, NULL);
	ft_strcat(champ->comment, word->str);
	if (word->next && (g_input_l = string->nbr))
		lex_error(ERR_UNEXPECTED_TOKEN, word->next->str);
	if (!word->quote_is_open)
		return (1);
	return (0);
}

int				comment(t_champion *champ, t_string *string)
{
	t_word		*word;
	int			to_return;

	to_return = -1;
	if (champ->comment_size != -1)
		lex_error(ERR_COMMENT_EXISTS, NULL);
	while (string)
	{
		to_return++;
		word = string->word;
		while (word && !word->is_quote)
		{
			if (champ->comment_size != -1 && !word->is_quote)
				return (to_return);
			word = word->next;
		}
		if (!word)
			return (to_return);
		if (concat_comment(champ, string, word) == 1)
			return (to_return);
		string = string->next;
	}
	return (to_return);
}
