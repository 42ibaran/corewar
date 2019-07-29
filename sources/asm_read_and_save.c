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

/*
** check_args() checks if the name of the file is given,
** checks if the name of the file is valid and tries to open the file
*/
int		check_args(int ac, char **av)
{
	char	*pos;

	if (ac == 1)
		error(ERR_USAGE);
	pos = ft_strstr(av[ac - 1], ".s");
	if (!pos || ft_strcmp(pos, ".s") || pos == av[ac - 1])
		error(ERR_USAGE);
	return (open(av[ac - 1], O_RDONLY));
}

/*
** define() uses functions word_is_*** trying to give a word a definition
*/
t_word		*define(char *line, int j, int i, char prev_quote)
{
	t_word		*word;

	word = init_word(line, j, i);
	word_is_space(line, j, i, word, prev_quote);
	word_is_quote(line, j, i, word, prev_quote);
	word_is_separator(line, j, i, word, prev_quote);
	if (!word->is_space && !word->is_quote && !word->is_separator)
	{
		word_is_command(line, j, i, word, prev_quote);
		word_is_instruction(line, j, i, word, prev_quote);
		word_is_operation(line, j, i, word, prev_quote);
		word_is_label(line, j, i, word, prev_quote);
		word_is_register(line, j, i, word, prev_quote);
		word_is_direct(line, j, i, word, prev_quote);
		word_is_indirect(line, j, i, word, prev_quote);
	}
	return (word);
}

char	word_is_something(t_word *word)
{
	return (word->is_command || word->is_instruction || word->is_operation
		|| word->is_label || word->is_register || word->is_direct
		||word->is_indirect || word->is_quote || word->is_separator);
}

void	define_and_remember(char *line, int i, int j, t_string *string,
		char prev_quote)
{
	t_word		*word;

	word = define(line, i, j, prev_quote);
	if (word && word_is_something(word))
	{
		if (!string->last_word)
			string->word = word;
		else
			string->last_word->next = word;
		string->last_word = word;
	}
	else if (word)
	{
		free(word->str);
		free(word);
	}
}

void	divide_string_into_words(char *line, t_string *string)
{
	static char		quote = 0;
	int				i = 0;
	int				j = 0;

	while (line[i])
	{
		if (line[i] == COMMENT_CHAR && !quote)
			break ;
		else if (line[i] == '\"')
		{
			if (quote || j != i)
				define_and_remember(line, j, i - 1, string, quote);
			quote = (quote == 0 ? 1 : 0);
			i++;
			j = i;
			continue ;
		}
		else if (!quote && (line[i] == SEPARATOR_CHAR || line[i] == ' '
				|| line[i] == '\t' || line[i] == '\n'))
		{
			if (i != j)
			{
				define_and_remember(line, j, i - 1, string, quote);
				define_and_remember(line, i, i, string, quote);
			}
			if (line[i] == '\n')
				return ;
			i++;
			j = i;
			continue ;
		}
		i++;
	}
	if (quote || j != i)
		define_and_remember(line, j, i - 1, string, quote);
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
		while ((ac = get_next_line(fd, &line)) == 1 && ++nbr)
		{
			g_input_l = nbr;
			new_string(&string, &next_string, nbr);
			next_string->line = line;
			divide_string_into_words(line, next_string);
		}
		if (ac == -1)
			error(ERR_READ);
		close(fd);
	}
	else
		error(ERR_READ);
	//print_strings(string);
	g_input_l = 0;
	return (string);
}
