/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:31:39 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 16:05:50 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_arg() takes a word and an array of function pointers that was created
** by get_f_arr() and checks if an argument is a register, direct or indirect
** depending on intruction and allowed types of argument
*/

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

/*
** check_sep() checks if a word is separator located in the right position
*/

void	check_sep(t_word **word, char *oper)
{
	*word = (*word)->next;
	if (!*word || !(*word)->is_separator)
		lex_error(ERR_SEPARATOR, oper);
}

/*
** check_null() checks if a word is null which means that there're no extra
** arguments
*/

void	check_null(t_word **word, char *oper)
{
	*word = (*word)->next;
	if (*word)
		lex_error(ERR_TOO_MANY_ARGS, oper);
}

void	check_label_chars(char *line, int i, int j)
{
	while (j < i)
	{
		if (!ft_strchr(LABEL_CHARS, *(line + j)))
			lex_error(ERR_INVALID_LABEL, NULL);
		j++;
	}
}
