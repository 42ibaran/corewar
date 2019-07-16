/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_and_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/16 14:57:47 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

int		check_args(int ac, char **av)
{
	char	*pos;

	if (ac == 1)
		error(-1);
	pos = ft_strstr(av[ac - 1], ".s");
	if (!pos || ft_strcmp(pos, ".s") || pos == av[ac - 1])
		error (-1);
	return (open(av[ac - 1], O_RDONLY));
}

t_lexer		*define(char *line, int j, int i, t_lexer *lexer)
{
	char	is_first;

	is_first = 0;
	if (j > i)
	{
		if (lexer && lexer->is_label == 0 && lexer->is_register == 0
				&& lexer->is_separator == 0 && lexer->is_direct == 0
				&& lexer->is_name == 0 && lexer->is_comment == 0
				&& lexer->is_space == 0 && lexer->is_command == 0)
			lexer->is_instruction = 1;
		if (lexer && (lexer->is_label != 0 || lexer->is_instruction != 0
				|| lexer->is_separator != 0 || lexer->is_direct != 0
				|| lexer->is_name != 0 || lexer->is_comment != 0
				|| lexer->is_space != 0 || lexer->is_command != 0))
			lexer->is_register = 0;
		return (lexer);
	}
	if (!lexer && ++is_first)
		lexer = init_lexer(line, j, i);
	if (line[j] == LABEL_CHAR)
		lexer->is_label = 1;
	if (line[j] == 'r' && is_first)
		lexer->is_register = 1;
	if (line[j] == '.' && is_first)
		lexer->is_command = 1;
	if (line[j] == DIRECT_CHAR)
		lexer->is_direct = 1;
	if (line[j] == SEPARATOR_CHAR)
		lexer->is_separator = 1;
	if ((line[j] == ' ' || line[j] == '\t' || line[j] == '\n') && is_first)
		lexer->is_space = 1;
	return (define(line, j + 1, i, lexer));
}

void	define_and_remember(char *line, int i, int j, t_string *string)
{
	t_lexer		*lexer;

	lexer = define(line, i, j, NULL);
	if (!string->last_word)
		string->word = lexer;
	else
		string->last_word->next = lexer;
	string->last_word = lexer;
}

void	lex(char *line, int i, int j, t_string *string)
{
	static char		quote = 0;
	char			prev_quote;

	prev_quote = quote;
	if (!line[i])
		return ;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '"')
			quote = (quote == 0 ? 1 : 0);
		if (line[i] == COMMENT_CHAR || line[i] == SEPARATOR_CHAR
				|| line[i] == ' ' || line[i] == '\t' || line[i] == '"')
			break ;
		i++;
	}
	if (!quote && !prev_quote && i != j)
	{
		define_and_remember(line, j, i - 1, string);
		if (line[i] != '\n')
			define_and_remember(line, i, i, string);
	}
	if (line[i] == COMMENT_CHAR)
		return ;
	lex(line, i + 1, i + 1, string);
}

void	new_string(t_string **string, t_string **next_string)
{
	if (!*string)
	{
		*string = init_string();
		*next_string = *string;
	}
	else
	{
		(*next_string)->next = init_string();
		(*next_string) = (*next_string)->next;
	}
}

void	check_and_read(int ac, char **av)
{
	int			fd;
	char		*line;
	t_string	*string = NULL;
	t_string	*next_string;
	
	if ((fd = check_args(ac, av)) >= 0)
	{
		while (get_next_line(fd, &line) == 1)
		{
			if (line[0] == '\n')
				continue ;
			new_string(&string, &next_string);
			lex(line, 0, 0, next_string);
			free(line);
		}
	}
	else
		error(-2);
	print_strings(string);
}
