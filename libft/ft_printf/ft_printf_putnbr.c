/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:03:40 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:19:00 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_puthex(unsigned long nbr, char c)
{
	char	*base;
	int		count;

	count = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		count += ft_puthex((nbr / 16), c);
		count += ft_puthex((nbr % 16), c);
	}
	else
		count += write(1, &base[nbr], 1);
	return (count);
}

int	ft_putptr(unsigned long nbr)
{
	int		count;

	if (!nbr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += ft_puthex(nbr, 'x');
	return (count);
}

int	ft_putnbr(int nbr)
{
	long	n;
	int		count;

	count = 0;
	n = nbr;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	if (n <= 9)
	{
		n += 48;
		count += write(1, &n, 1);
	}
	return (count);
}

int	ft_putunsignednbr(unsigned int nbr)
{
	unsigned long	n;
	int				count;

	n = nbr;
	count = 0;
	if (n > 9)
	{
		count += ft_putnbr(n / 10);
		count += ft_putnbr(n % 10);
	}
	if (n <= 9)
	{
		n += 48;
		count += write(1, &n, 1);
	}
	return (count);
}
