/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 10:01:47 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_str(t_lexer *node)
{
	while (node)
	{
		ft_printf("%s", node->str);
		if (node->next)
			ft_printf(" ");
		node = node->next;
	}
}

void	echo(t_mshell *init)
{
	t_lexer	*node;
	int		flag;
	int		i;
	
	flag = 0;
	i = 2;
	node = init->lexer->next;
	if (node->str[i - 2] == '-' && node->str[i - 1] == 'n')
	{
		while (node->str[i] == 'n')
			i++;
		if (!node->str[i])
		{
			flag = 1;
			node = node->next;
		}
	}
	print_str(node);
	if (flag == 0)
		ft_printf("\n");
	return ;
}
