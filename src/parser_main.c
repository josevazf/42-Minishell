/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/02 11:55:15 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* Search Lexer list for a Pipe and return the corresponding node */
t_lexer	*find_pipe(t_lexer *tokens)
{
	while (tokens && (tokens->operator != PIPE))
		tokens = tokens->next;
	return (tokens);
}

int		parser_main(t_mshell *init)
{
	t_parser	*head;
	
	head = NULL;
	
	parser_tree = (t_parser *)malloc(sizeof(t_parser));
	head = parser_tree;
	parser_tree->left = NULL;
	parser_tree->type = CMD;
	while (tokens)
	{
		parser_tree->left = NULL;
		while (tokens->operator != TYPE_PIPE)
			tokens = tokens->next;
	}
}
