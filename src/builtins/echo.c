/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/29 13:42:40 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_str(char **str, int j)
{
	while (str[j])
	{
		printf("%s", str[j]);
		if (str[j + 1])
			printf(" ");
		j++;
	}
}

void	echo(t_parser *parser, int i, int j, t_mshell *init)
{
	int		flag;

	flag = 0;
	if (!parser->cmd_exec[j])
		flag = 0;
	while (parser->cmd_exec[j] && parser->cmd_exec[j][0] == '-' \
							&& parser->cmd_exec[j][1] == 'n')
	{
		i = 2;
		while (parser->cmd_exec[j][i] == 'n')
			i++;
		if (!parser->cmd_exec[j][i])
		{
			flag = 1;
			j++;
		}
		else
			break ;
	}
	if (parser->cmd_exec[j])
		print_str(parser->cmd_exec, j);
	if (flag == 0)
		printf("\n");
	delete_lists(init);
	exit (0);
}
