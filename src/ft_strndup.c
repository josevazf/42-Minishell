/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 22:39:47 by patatoss          #+#    #+#             */
/*   Updated: 2023/12/21 22:54:55 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*s_dup;

	i = 0;
	s_dup = malloc(sizeof(char) * (ft_strlen(s) - n + 1) + 1);
	if (!s_dup)
		return (NULL);
	while (s[n])
	{
		s_dup[i++] = s[n++];
	}
	s_dup[i] = '\0';
	return (s_dup);
}
