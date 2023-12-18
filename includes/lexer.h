/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2023/12/18 09:55:12 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define TYPE_CMD 1
# define TYPE_PIPE 2
# define TYPE_GREAT 3
# define TYPE_DOU_GREAT 4
# define TYPE_LESS 5
# define TYPE_DOU_LESS 6

typedef struct s_lexer
{
	char	*str;
	int		operator;
	int		i;
	struct	s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

// lexer.c
t_lexer	*lexer_list(char **args);
int		lexer_main(char *input, char **envp);

// lexer_split.c
char	**lexer_split(char const *s);

// lexer_cmd.c
// char	**parse_path(char **envp);
// char	*get_cmd_path(char **envp_paths, char *cmd);
// void	find_cmd(t_lexer *tokens, char **envp);
// int		cmd_router(char *cmd);

#endif
