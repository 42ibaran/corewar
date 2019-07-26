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
** define() uses functions word_is_*** trying to give a word a definition
*/
t_word		*define(char *line, int j, int i, t_word *word, char prev_quote)
{
	word = init_word(line, j, i);
	word_is_space(line, j, i, word, prev_quote);
	word_is_quote(line, j, i, word, prev_quote);
	word_is_separator(line, j, i, word, prev_quote);
	if (!word->is_space && !word->is_quote && !word->is_separator)
	{
		word_is_command(line, j, i, word, prev_quote);
		word_is_instruction(line, j, i, word, prev_quote);
		word_is_operation(line, j, i, word, prev_quote);
		word_is_register(line, j, i, word, prev_quote);
		word_is_direct(line, j, i, word, prev_quote);
		word_is_indirect(line, j, i, word, prev_quote);
		word_is_label(line, j, i, word, prev_quote);
	}
	return (word);
}

void	define_and_remember(char *line, int i, int j, t_string *string,
		char prev_quote)
{
	t_word		*word;

	word = define(line, i, j, NULL, prev_quote);
	if (word && !word->is_space)
	{
		if (!string->last_word)
			string->word = word;
		else
			string->last_word->next = word;
		string->last_word = word;
	}
}

void	lex(char *line, int i, int j, t_string *string)
{
	static char		quote = 0;
	char			prev_quote;

	prev_quote = quote;
	if (!line[i])
		return ;
	while (line[i])// && line[i] != '\n')
	{
		if (line[i] == '"')
		{
			quote = (quote == 0 ? 1 : 0);
			break ;
		}
		if (!quote && (line[i] == COMMENT_CHAR || line[i] == SEPARATOR_CHAR
				|| line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
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
			next_string->line = line;
			lex(line, 0, 0, next_string);
			//free(line);
		}
		close(fd);
	}
	else
		error(ERR_READ);
	print_strings(string);
	return (string);
}
