/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_read_and_save.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/09/10 11:18:44 by ibaran           ###   ########.fr       */
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
	if (!pos || ft_strcmp(pos, ".s"))
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

static char		is_end_of_word(char *line, int i, int j)
{
	return (line[i] == SEPARATOR_CHAR || line[i] == ' '
		|| line[i] == '\t' || line[i] == '\n' || line[i] == '\"'
		|| (line[i] == DIRECT_CHAR && i != j)
		|| (line[i] == LABEL_CHAR && i != j
		&& i != 0 && line[i - 1] != DIRECT_CHAR));
}

/*
** divide_string_into_words() takes line and divides it into sub-lines
** with separtors, spaces and quotes. it stops dividing the string if
** it reaches comment chars
** P.S. the creator is sorry for sending i as an argument
*/

static void		divide_string_into_words(char *line, t_string *string, int i)
{
	static char		quote = 0;
	int				j;

	j = 0;
	while (line[++i])
	{
		if ((line[i] == COMMENT_CHAR || line[i] == DEF_COMMENT_CHAR) && !quote)
			break ;
		if (is_end_of_word(line, i, j) && (!quote || line[i] == '\"'))
		{
			add_word(allocate_and_define(line, j, i - (line[i] != LABEL_CHAR),
					quote), string);
			if (line[i] != '\"' && line[i] != DIRECT_CHAR
					&& line[i] != LABEL_CHAR)
				add_word(allocate_and_define(line, i, i, quote), string);
			else if (line[i] == '\"')
				quote = (quote == 0 ? 1 : 0);
			j = (i -= (line[i] == DIRECT_CHAR)) + 1;
		}
		if (!quote && line[i] == '\n')
			return ;
	}
	add_word(allocate_and_define(line, j, i - 1, quote), string);
	if (!quote && line[i] == '\0' && string->last_word)
		error(ERR_END);
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
			divide_string_into_words(line, next_string, -1);
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
