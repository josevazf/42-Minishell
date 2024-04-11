/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 07:57:15 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/11 11:57:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_echo_behind(t_lexer *lex_nd)
{
	while (lex_nd->prev)
	{
		if (ft_strcmp(lex_nd->prev->str, "echo") == 0)
			return (true);
		lex_nd = lex_nd->prev;
	}
	return (false);
}

bool	invalid_echo_option(char *str, int fd)
{
	if (str && str[0] && str[0] == '-')
		if (str && str[1] && str[1] != 'n')
		{
			write(fd, "minishell: invalid echo option", 30);
			return (true);
		}
	return (false);
}

void	print_str(t_mshell *init, t_lexer *lex_nd, int fd)
{
	if (is_echo_behind(lex_nd) == false)
	{
		while (lex_nd && lex_nd->str && ft_strcmp(lex_nd->str, "echo") != 0)
			lex_nd = lex_nd->next;
		lex_nd = lex_nd->next;
	}
	while (lex_nd)
	{
		if (invalid_echo_option(lex_nd->str, fd) == true)
			break ;
		if ((ft_strcmp(lex_nd->str, "<<") == 0 || \
		ft_strcmp(lex_nd->str, ">>") == 0 || \
		ft_strcmp(lex_nd->str, "<") == 0 || \
		ft_strcmp(lex_nd->str, ">") == 0) && lex_nd->true_sign == true)
			break ;
		if (ft_strcmp(lex_nd->str, "^") != 0 && !init->var_nf)
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
		print_str(init, lex_nd, parser->output);
	if (flag == 0 || !lex_nd)
		write(parser->output, "\n", 1);
	delete_lists(init);
	exit (0);
}
