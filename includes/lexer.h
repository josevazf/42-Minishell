/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/02 11:28:59 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "expander.h"

# define CMD 1
# define PIPE 2
# define GREAT 3
# define DOU_GREAT 4
# define LESS 5
# define DOU_LESS 6

typedef struct s_lexer
{
	char			*str;
	int				operator;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

// lexer.c
t_lexer	*lexer_list(char **args);
int 	lexer_main(t_mshell *init, char *input);

// lexer_split.c
char	**lexer_split(char const *s);

// lexer_elements.c
int		lexer_elements(char const *s);

// lexer_quotes_checker.c
void	quotes_checker(char const *s);

// lexer_cmd.c
// char	**parse_path(char **envp);
// char	*get_cmd_path(char **envp_paths, char *cmd);
// void	find_cmd(t_lexer *tokens, char **envp);
// int		cmd_router(char *cmd);

#endif
