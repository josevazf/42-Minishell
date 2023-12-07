/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:55:40 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:21:10 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr != NULL)
	{
		while (s1[i])
		{
			newstr[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			newstr[i] = s2[j];
			i++;
			j++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
