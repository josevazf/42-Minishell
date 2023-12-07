/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:02:09 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:20:40 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	if (dest < src)
	{
		i = -1;
		while (++i < n)
			p_dest[i] = p_src[i];
	}
	else
	{
		i = n - 1;
		while ((int)i >= 0)
		{
			p_dest[i] = p_src[i];
			i--;
		}
	}
	return (dest);
}
