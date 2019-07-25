/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 15:30:38 by ibaran            #+#    #+#             */
/*   Updated: 2019/07/24 15:51:46 by ibaran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "asm.h"

void	write_into_file(t_output *out, char *name)
{
	int		fd;

	name[ft_strlen(name) - 2] = '\0';
	if ((fd = open(name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
		error(ERR_WRITE);
	write(fd, out->string, out->size);
	close(fd);
}
