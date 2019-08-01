/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_operations_6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/01 14:55:22 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_arg(t_word **word, t_check_arg *f, char *oper)
{
	char	ok;
	void	*rem_f;

	rem_f = f;
	ok = 0;
	*word = (*word)->next;
	if (!*word)
	{
		free(rem_f);
		lex_error(ERR_NOT_ENOUGH_ARGS, oper);
	}
	while (*f)
	{
		if ((*f)(*word))
			ok = 1;
		f++;
	}
	if (!ok)
	{
		free(rem_f);
		lex_error(ERR_WRONG_ARG_TYPE, oper);
	}
	free(rem_f);
}

void	check_sep(t_word **word, char *oper)
{
	*word = (*word)->next;
	if (!*word || !(*word)->is_separator)
		lex_error(ERR_SEPARATOR, oper);
}

void	check_null(t_word **word, char *oper)
{
	*word = (*word)->next;
	if (*word)
		lex_error(ERR_TOO_MANY_ARGS, oper);
}
