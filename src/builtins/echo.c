/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/03 00:53:19 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_str(char **str, int j, int fd)
{
	while (str[j])
	{
		write(fd, str[j], ft_strlen(str[j]));
		if (str[j + 1])
			write(fd, " ", 1);
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
		print_str(parser->cmd_exec, j, init->parser->output);
	if (flag == 0)
		write(init->parser->output, "\n", 1);
	delete_lists(init);
	exit (0);
}
