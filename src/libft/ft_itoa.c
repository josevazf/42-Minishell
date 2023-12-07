/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:58:40 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:20:04 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	num_size(long n)
{
	size_t	size;

	size = 1;
	if (n < 0)
		n = -n * 10;
	while (n > 9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*arr;
	size_t	i;
	long	n;

	n = nb;
	arr = malloc(sizeof(char) * (num_size(n) + 1));
	if (!arr)
		return (NULL);
	if (n < 0)
		arr[0] = '-';
	i = num_size(n);
	arr[i] = '\0';
	if (n < 0)
		n = -n;
	while (n > 9)
	{
		arr[--i] = (n % 10) + '0';
		n /= 10;
	}
	arr[--i] = n + '0';
	return (arr);
}
