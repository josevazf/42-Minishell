/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/01 19:33:58 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(t_parser *parser, int i, int j)
{
	int		flag;

	flag = 0;
	if (!parser->cmd_exec[j])
		flag = 0;
	else if (parser->cmd_exec[j][0] == '-' && parser->cmd_exec[j][1] == 'n')
	{
		while (parser->cmd_exec[j][i] && parser->cmd_exec[j][i] == 'n')
			i++;
		if (!parser->cmd_exec[j][i])
			flag = 1;
		j++;
	}
	if (parser->cmd_exec[j])
		while (parser->cmd_exec[j])
		{
			printf("%s", parser->cmd_exec[j++]);
			if (parser->cmd_exec[j])
				printf(" ");
		}
	if (flag == 0)
		printf("\n");
	exit (0);
}
