/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:22:10 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/06 07:43:50 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *stash, int c)
{
	if (!stash)
		return (NULL);
	while (*stash && (unsigned char)c != *stash)
		stash++;
	if ((unsigned char)c == *stash)
		return ((char *)stash);
	return (NULL);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*nstash;

	i = 0;
	j = 0;
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		stash[0] = '\0';
	}
	nstash = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer) + 1));
	if (!nstash)
		return (NULL);
	while (stash[i])
	{
		nstash[i] = stash[i];
		i++;
	}
	while (buffer[j])
		nstash[i++] = buffer[j++];
	nstash[i] = '\0';
	free(stash);
	return (nstash);
}

char	*ft_strdup_break(char *stash)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (!stash[i])
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(sizeof(char) * len + 2);
	if (!line)
		return (NULL);
	while (i <= len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*refresh_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash [i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (++i < ft_strlen(stash))
		new_stash[j++] = stash[i];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
