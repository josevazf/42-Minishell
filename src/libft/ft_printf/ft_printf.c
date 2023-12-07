/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:31:42 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 09:19:14 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	check_case(char c, va_list al)
{
	int	count;

	count = 0;
	if (c == '%')
		count += write(1, "%%", 1);
	else if (c == 'c')
		count += ft_printf_putchar(va_arg(al, int));
	else if (c == 's')
		count += ft_printf_putstr(va_arg(al, char *));
	else if (c == 'p')
		count += ft_putptr(va_arg(al, unsigned long));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(al, long));
	else if (c == 'u')
		count += ft_putunsignednbr(va_arg(al, unsigned int));
	else if (c == 'x')
		count += ft_puthex(va_arg(al, unsigned int), 'x');
	else if (c == 'X')
		count += ft_puthex(va_arg(al, unsigned int), 'X');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	al;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(al, str);
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += check_case(str[++i], al);
			i++;
		}
		else
			count += write(1, &str[i++], 1);
	}
	va_end(al);
	return (count);
}

/* int main()
{
	int x = 1;
	
	ft_printf("Percentagem %%\n");
	ft_printf("Caracter: %c\n", 'T');
	ft_printf("String: %s\n", "Frase");
	ft_printf("Pointer: %p\n", &x);
	ft_printf("Integer: %i\n", -42);
	ft_printf("Decimal: %d\n", -42);
	ft_printf("Unsigned: %u\n", 42);
	ft_printf("Hexa lower: %x\n", 14);
	ft_printf("Hexa upper: %X\n", 15);

} */