/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/13 12:10:25 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define TYPE_S_CMD 1
# define TYPE_B_CMD 2
# define TYPE_ARG 3
# define TYPE_TEXT 4
# define TYPE_PIPE 5
# define TYPE_REDIR 6

typedef struct s_lexer
{
	int		type;
	char	*input;
	char	*path;
	struct s_lexer *next;
}	t_lexer;

// lexer.c
t_lexer	*lexer_list(char **args);
int		lexer_main(char *input, char **envp);

// lexer_split.c
char	**lexer_split(char const *s);

// lexer_cmd.c
char	**parse_path(char **envp);
char	*get_cmd_path(char **envp_paths, char *cmd);
void	find_cmd(t_lexer *tokens, char **envp);
int		cmd_router(char *cmd);

#endif
