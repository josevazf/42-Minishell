/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:31:25 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/09/29 16:53:47 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_text(int fd, char *bufftxt)
{
	char	*temp;
	int		rbytes;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	rbytes = 1;
	while (!ft_strchr2(bufftxt, '\n') && rbytes != 0)
	{
		rbytes = read(fd, temp, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(temp);
			free(bufftxt);
			return (NULL);
		}
		temp[rbytes] = '\0';
		bufftxt = ft_strjoin2(bufftxt, temp);
	}
	free(temp);
	return (bufftxt);
}

char	*get_next_line(int fd)
{
	static char	*bufftxt;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bufftxt = ft_get_text(fd, bufftxt);
	if (!bufftxt)
		return (NULL);
	line = ft_strtrim_l(bufftxt);
	bufftxt = ft_strtrim_r(bufftxt);
	return (line);
}

/* int	main(void)
{
	char	*line;
	char	*line2;
	char	*line3;
	int		i;
	int		fd;
	
	i = 0;
	fd = open("docs/text1.txt", O_RDONLY);
	while (i < 7)
	{
		line = get_next_line(fd);
		printf(" %s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
} */