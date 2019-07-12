/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_check_and_read.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 15:57:01 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/12 15:40:45 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

t_lexer		*alloc_lexer(char *line, int j, int i)
{
	t_lexer		*lexer;
	
	if (!(lexer = (t_lexer*)malloc(sizeof(t_lexer))))
		error(1);
	if (!(lexer->str = ft_strndup(line + j, i - j + 1)))
		error(1);
	lexer->is_label = 0;
	lexer->is_instruction = 0;
	lexer->is_register = 0;
	lexer->is_separator = 0;
	lexer->is_direct = 0;
	lexer->is_name = 0;
	lexer->is_comment = 0;
	lexer->is_space = 0;
	lexer->is_command = 0;
	return (lexer);
}

/*
** For now define_and_remember() is more like only_define()
*/

t_lexer		*define_and_remember(char *line, int j, int i, t_lexer *lexer)
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
		lexer = alloc_lexer(line, j, i);
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
	return (define_and_remember(line, j + 1, i, lexer));
}

void		print_definition(t_lexer *lexer)
{
	if (!lexer)
		return ;
	if (lexer->is_label)
		ft_printf(" label ");
	if (lexer->is_instruction)
		ft_printf(" instruction ");
	if (lexer->is_register)
		ft_printf(" register ");
	if (lexer->is_separator)
		ft_printf(" separator ");
	if (lexer->is_direct)
		ft_printf(" direct ");
	if (lexer->is_name)
		ft_printf(" name ");
	if (lexer->is_comment)
		ft_printf(" comment ");
	if (lexer->is_command)
		ft_printf(" command ");
}

void	define_and_print(char *line, int i, int j)
{
	t_lexer		*lexer;

	lexer = define_and_remember(line, i, j, NULL);
	if (!lexer->is_space)
	{
		ft_printf("%s ", lexer->str);
		print_definition(lexer);
		ft_printf("\n");
	}
	if (lexer)
		free(lexer);
}

void	lex(char *line, int i, int j)
{
	static char		quote = 0;
	char			prev_quote;

	prev_quote = quote;
	if (!line[i])
		return ;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == COMMENT_CHAR || line[i] == SEPARATOR_CHAR
				|| line[i] == ' ' || line[i] == '\t')
			break ;
		if (line[i] == '"')
			quote = (quote == 0 ? 1 : 0);
		i++;
	}
	if (!quote && !prev_quote && i != j)
	{
		define_and_print(line, j, i - 1);
		define_and_print(line, i, i);
	}
	if (line[i] == COMMENT_CHAR)
		return ;
	lex(line, i + 1, i + 1);
}

void	check_and_read(int ac, char **av)
{
	int		fd;
	char	*line;
	
	if ((fd = check_args(ac, av)) >= 0)
	{
		
		while (get_next_line(fd, &line) == 1)
		{
			if (line[0] == '\n')
				continue ;
			lex(line, 0, 0);
			ft_printf("\n");
			free(line);
		}
	}
	else
		error(-2);
}
