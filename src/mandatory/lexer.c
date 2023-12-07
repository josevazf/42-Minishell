/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/07 12:38:03 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lexer	*lexer_list(char **args)
{
	int		i;
	int		j;
	t_lexer *lexer_list;
	t_lexer *head;

	i = 0;
	lexer_list = (t_lexer *)malloc(sizeof(t_lexer));
	head = lexer_list;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			j++;
		lexer_list->input = (char *)malloc(sizeof(char) * j + 1);
		lexer_list->input[j] = '\0';
		while (--j >= 0)
			lexer_list->input[j] = args[i][j];
		lexer_list->next = NULL;
		if (args[++i])
		{
			lexer_list->next = (t_lexer *)malloc(sizeof(t_lexer));
			lexer_list = lexer_list->next;
		}
	}
	return (head);
}
	
int main(void)
{
	t_lexer 	*lexer;
	char		*line;
	char		**args;
	int			i;

	i = 0;
	line = readline("Minishell$: ");
	args = lexer_split(line);
	lexer = lexer_list(args);
	// TEST START
	while (lexer)
	{
		printf("%s\n", lexer->input);
		lexer = lexer->next;
	}
	// TEST END
	return (0);
}
