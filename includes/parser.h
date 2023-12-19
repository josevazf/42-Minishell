/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:08:41 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/18 12:24:45 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define CMD 1;
# define PIPE 2;

typedef struct s_node
{
	int		type;
	char	**execute;
	t_lexer	in_red;
	t_lexer	out_red;
	struct t_node *left;
	struct t_node *right;
}	t_node;

// parser_main.c
int		parser_main(t_lexer *data);

#endif
