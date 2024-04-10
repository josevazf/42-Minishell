/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/10 19:31:15 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_str(t_lexer *lex_nd, int fd)
{
	while (lex_nd)
	{
		if ((ft_strcmp(lex_nd->str, "<<") == 0 || \
		ft_strcmp(lex_nd->str, ">>") == 0 || \
		ft_strcmp(lex_nd->str, "<") == 0 || \
		ft_strcmp(lex_nd->str, ">") == 0) && lex_nd->true_sign == true)
			break ;
		write(fd, lex_nd->str, ft_strlen(lex_nd->str));
		if (lex_nd->next)
			write(fd, " ", 1);
		lex_nd = lex_nd->next;
	}
}

void	echo(t_mshell *init, t_parser *parser, t_lexer *lex_nd, int i)
{
	int		flag;

	flag = 0;
	lex_nd = lex_nd->next;
	if (!lex_nd || !lex_nd->str)
		flag = 0;
	while (lex_nd && lex_nd->str && lex_nd->str[0] == '-' \
							&& lex_nd->str[1] == 'n')
	{
		i = 2;
		while (lex_nd->str[i] == 'n')
			i++;
		if (!lex_nd->str[i])
			flag = 1;
		else
			break ;
		lex_nd = lex_nd->next;
	}
	if (lex_nd && lex_nd->str)
		print_str(lex_nd, parser->output);
	if (flag == 0 || !lex_nd)
		write(parser->output, "\n", 1);
	delete_lists(init);
	exit (0);
}
