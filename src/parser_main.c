/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:06:55 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/18 12:40:06 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int		count_pipes(t_lexer *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->operator == TYPE_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

/* void	create_pipe_node(t_lexer *tokens, int type)
{
	t_node	*node;
	
	
	
} */

int		parser_main(t_lexer *tokens)
{
	t_node	*parser_tree;
	t_node	*head;
	int		n_pipes;
	
	n_pipes = count_pipes(tokens);
	parser_tree = (t_node *)malloc(sizeof(t_node));
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