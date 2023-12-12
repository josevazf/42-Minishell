/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/12 14:40:08 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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
	
int lexer_main(char *input, char **envp)
{
	t_lexer 	*tokens;
	char		**args;
	int			i;

	i = 0;
	args = lexer_split(input);
	tokens = lexer_list(args);
	// TEST START
	while (tokens)
	{
		find_cmd(tokens, envp);
		printf("token: %s\n", tokens->input);
		tokens = tokens->next;
	}
	// TEST END
	return (0);
}
