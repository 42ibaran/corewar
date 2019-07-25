/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read_and_save.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 13:05:08 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "corewar.h"

/*
** check_args() checks if the name of the file is given,
** checks if the name of the file is valid and tries to open the file
*/
int		check_args(int ac, char **av)
{
	char	*pos;

	if (ac == 1)
		error(-1);
	pos = ft_strstr(av[ac - 1], ".s");
	if (!pos || ft_strcmp(pos, ".s") || pos == av[ac - 1])
		error(ERR_USAGE);
	return (open(av[ac - 1], O_RDONLY));
}

/*
** define() takes the part if a line and checks every character trying to give
** a word a definition
*/
t_word		*define(char *line, int j, int i, t_word *word, char prev_quote)
{
	char	is_first;

	is_first = 0;
	if (j > i)
	{
		if (word && word->is_label == 0 && word->is_register == 0
				&& word->is_separator == 0 && word->is_direct == 0
				&& word->is_name == 0 && word->is_comment == 0
				&& word->is_space == 0 && word->is_command == 0
				&& word->is_quote == 0)
			word->is_instruction = 1;
		if (word && (word->is_label != 0 || word->is_instruction != 0
				|| word->is_separator != 0 || word->is_direct != 0
				|| word->is_name != 0 || word->is_comment != 0
				|| word->is_space != 0 || word->is_command != 0
				|| word->is_quote != 0))
			word->is_register = 0;
		return (word);
	}
	if (!word && ++is_first)
		word = init_word(line, j, i);
	if (line[j] == LABEL_CHAR)
		word->is_label = 1;
	if (line[j] == 'r' && is_first)
		word->is_register = 1;
	if (line[j] == '.' && is_first)
		word->is_command = 1;
	if (line[j] == DIRECT_CHAR)
		word->is_direct = 1;
	if (line[j] == SEPARATOR_CHAR)
		word->is_separator = 1;
	if ((line[j] == ' ' || line[j] == '\t' || line[j] == '\n') && is_first)
		word->is_space = 1;
	if (prev_quote)
	{
		word->is_quote = 1;
		j = i;
	}
	return (define(line, j + 1, i, word, prev_quote));
}

void	define_and_remember(char *line, int i, int j, t_string *string,
		char prev_quote)
{
	t_word		*word;

	word = define(line, i, j, NULL, prev_quote);
	if (!string->last_word)
		string->word = word;
	else
		string->last_word->next = word;
	string->last_word = word;
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
		{
			quote = (quote == 0 ? 1 : 0);
			break ;
		}
		if (!quote && (line[i] == COMMENT_CHAR || line[i] == SEPARATOR_CHAR
				|| line[i] == ' ' || line[i] == '\t'))
			break ;
		i++;
	}
	if (i != j)
	{
		define_and_remember(line, j, i - 1, string, prev_quote);
		if (line[i] != '\n' && !prev_quote && !quote)
			define_and_remember(line, i, i, string, prev_quote);
	}
	if (line[i] == COMMENT_CHAR)
		return ;
	lex(line, i + 1, i + 1, string);
}

void	new_string(t_string **string, t_string **next_string, int nbr)
{
	if (!*string)
	{
		*string = init_string(nbr);
		*next_string = *string;
	}
	else
	{
		(*next_string)->next = init_string(nbr);
		(*next_string) = (*next_string)->next;
	}
}

t_string	*read_and_save(int ac, char **av)
{
	int			fd;
	char		*line;
	int			nbr = 0;
	t_string	*string = NULL;
	t_string	*next_string;
	
	if ((fd = check_args(ac, av)) >= 0)
	{
		while (get_next_line(fd, &line) == 1 && ++nbr)
		{
			if (line[0] == '\n')
				continue ;
			new_string(&string, &next_string, nbr);
			lex(line, 0, 0, next_string);
			free(line);
		}
		close(fd);
	}
	else
		error(ERR_READ);
	print_strings(string);
	return (string);
}
