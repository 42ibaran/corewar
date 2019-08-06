/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read_and_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/08/06 15:08:59 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** check_args() checks if the name of the file is given,
** checks if the name of the file is valid and tries to open the file
*/

static int		check_args(int ac, char **av)
{
	char	*pos;

	if (ac == 1)
		error(ERR_USAGE);
	pos = ft_strstr(av[ac - 1], ".s");
	if (!pos || ft_strcmp(pos, ".s") || pos == av[ac - 1])
		error(ERR_USAGE);
	return (open(av[ac - 1], O_RDONLY));
}

static void		add_word(t_word *word, t_string *string)
{
	if (!word)
		return ;
	if (!string->last_word)
		string->word = word;
	else
		string->last_word->next = word;
	string->last_word = word;
}

char		is_end_of_word(char *line, char quote, int i)
{
	return (!quote && (line[i] == SEPARATOR_CHAR || line[i] == ' '
		|| line[i] == '\t' || line[i] == '\n'));
}

/*
** divide_string_into_words() takes line and divides it into sub-lines
** with separtors, spaces and quotes. it stops dividing the string if
** it reaches coment chars
** P.S. the creator is sorry for sending j as a parameter (blame the norm)
*/

static void		divide_string_into_words(char *line, t_string *string, int j)
{
	static char		quote = 0;
	int				i;

	i = -1;
	while (line[++i])
	{
		if ((line[i] == COMMENT_CHAR || line[i] == DEF_COMMENT_CHAR) && !quote)
			break ;
		if (line[i] == '\"')
		{
			add_word(allocate_and_define(line, j, i - 1, quote), string);
			quote = (quote == 0 ? 1 : 0);
			j = i + 1;
		}
		else if (is_end_of_word(line, quote, i))
		{
			add_word(allocate_and_define(line, j, i - 1, quote), string);
			add_word(allocate_and_define(line, i, i, quote), string);
			if (line[i] == '\n')
				return ;
			j = i + 1;
		}
	}
	if (quote || j != i)
		add_word(allocate_and_define(line, j, i - 1, quote), string);
}

/*
** read_and_save() uses divide_string_into_words() on
** every not empty line that is obtained by gnl()
*/

t_string		*read_and_save(int ac, char **av)
{
	int			fd;
	char		*line;
	int			nbr;
	t_string	*string;
	t_string	*next_string;

	nbr = 0;
	string = NULL;
	if ((fd = check_args(ac, av)) >= 0)
	{
		while ((ac = get_next_line(fd, &line)) == 1 && ++nbr)
		{
			g_input_l = nbr;
			new_string(&string, &next_string, nbr);
			next_string->line = line;
			divide_string_into_words(line, next_string, 0);
		}
		if (ac == -1)
			error(ERR_READ);
		close(fd);
	}
	else
		error(ERR_READ);
	g_input_l = 0;
	return (string);
}
