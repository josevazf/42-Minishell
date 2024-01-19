/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 07:52:03 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 10:02:45 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer_router(t_lexer *tokens)
{
	while (tokens)
	{
		if (!ft_strcmp(tokens->str, "|"))
			tokens->operator = PIPE;
		else if (!ft_strcmp(tokens->str, ">"))
			tokens->operator = GREAT;
		else if (!ft_strcmp(tokens->str, ">>"))
			tokens->operator = DOU_GREAT;
		else if (!ft_strcmp(tokens->str, "<"))
			tokens->operator = LESS;
		else if (!ft_strcmp(tokens->str, "<<"))
			tokens->operator = DOU_LESS;
		else
			tokens->operator = CMD;
		tokens = tokens->next;
	}
}

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
		lexer_list->str = (char *)malloc(sizeof(char) * j + 1);
		lexer_list->str[j] = '\0';
		while (--j >= 0)
			lexer_list->str[j] = args[i][j];
		lexer_list->next = NULL;
		if (args[++i])
		{
			lexer_list->next = (t_lexer *)malloc(sizeof(t_lexer));
			lexer_list = lexer_list->next;
		}
	}
	return (head);
}
	
int lexer_main(t_mshell *init)
{
	expander(init);
	free_expander(init->expander);
	lexer_split(init);
	lexer_router(init->lexer);
	return (0);
}
