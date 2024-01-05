/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/02 22:32:55 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	echo(t_mshell *init)
{
	t_lexer	*node;
	int		flag;
	
	flag = 0;
	node = init->lexer;
	node = node->next;

	if (ft_strcmp(node->str, "-n") == 0)
	{
		flag = 1;
		node = node->next;
	}
	while (node)
	{
		ft_printf("%s", node->str);
		if (node->next)
			ft_printf(" ");
		node = node->next;
	}
	if (flag == 0)
		ft_printf("\n");
	return ;
}
