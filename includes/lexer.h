/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/12 14:45:03 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_lexer
{
	char	*type;
	char	*input;
	struct s_lexer *next;
}	t_lexer;

// lexer.c
t_lexer	*lexer_list(char **args);
int			lexer_main(char *input, char **envp);

// lexer_split.c
char	**lexer_split(char const *s);

// lexer_cmd.c
char	**parse_path(char **envp);
char	*get_cmd_path(char **envp_paths, char *cmd);
void	find_cmd(t_lexer *tokens, char **envp);
void	cmd_router(char *cmd);

#endif
