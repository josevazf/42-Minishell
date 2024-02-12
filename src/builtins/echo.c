/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/12 16:14:28 by tiaferna         ###   ########.fr       */
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

void	echo(t_parser *parser)
{
	int		flag;
	int		i;
	int		j;

	flag = 0;
	i = 2;
	j = 1;
	if (parser->cmd_exec[j][0] == '-' && parser->cmd_exec[j][1] == 'n')
	{
		while (parser->cmd_exec[j][i] && parser->cmd_exec[j][i] == 'n')
			i++;
		if (!parser->cmd_exec[j][i])
			flag = 1;
		j++;
	}
	if (parser->cmd_exec[j])
		printf("%s", parser->cmd_exec[j]);
	if (flag == 0)
		printf("\n");
	exit (0);
}
