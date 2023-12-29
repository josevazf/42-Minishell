/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/29 12:03:56 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

/* void	create_pipe_node(t_lexer *tokens, int type)
{
	t_node	*node;
	
	
	
} */

int		parser_main(t_mshell *init)
{
	t_node	*parser_tree;
	t_node	*head;
	
	parser_tree = (t_parser *)malloc(sizeof(t_parser));
	head = parser_tree;
	parser_tree->left = NULL;
	parser_tree->type = CMD;
	while (tokens->operator != TYPE_PIPE)
		tokens = tokens->next;
	while (tokens)
	{
		parser_tree->left = NULL;
		while (tokens->operator != TYPE_PIPE)
			tokens = tokens->next;
	}
}
