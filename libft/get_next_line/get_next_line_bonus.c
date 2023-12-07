/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:21:46 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/06 07:43:45 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_text(int fd, char *stash)
{
	char	*buffer;
	int		read_val;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_val = 1;
	while (read_val != 0 && !ft_strchr(stash, '\n'))
	{
		read_val = read(fd, buffer, BUFFER_SIZE);
		if (read_val == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[read_val] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	stash[fd] = get_text(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_strdup_break(stash[fd]);
	stash[fd] = refresh_stash(stash[fd]);
	return (line);
}
