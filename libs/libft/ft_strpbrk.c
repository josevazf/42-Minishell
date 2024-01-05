/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:01:07 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/03 11:02:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns a pointer to the first occurrence in 's1' of any of the characters
	that are part of 's2', or a null pointer if there are no matches. */
char 	*ft_strpbrk(const char *s1, const char *s2)
{
	int i = -1;
	int j = -1;
	
	while (s1[++i])
	{
		j = -1;
		while (s2[++j])
		{
			if (s1[i] == s2[j])
				return ((char *) s1 + i);
		}
	}
	return (NULL);
}
