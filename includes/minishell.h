/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/29 09:06:05 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
// # include "lexer.h"
// # include "expander.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR 1
# define SUCCESS 0
# define CMD_NOT_FOUND 127
# define IN_FILE 0
# define OUT_FILE 1

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_mshell
{
	int				nbr_pipes;
	int				nbr_cmds;
	struct s_env	*env_table;
	struct s_lexer	*lexer;
	//parser
}	t_mshell;

// minishell.c
/*---- main ----*/

// env_main.c
t_env	*create_envll(char **envp, int i);
t_env	*create_node(char *var, char *content);
void	node_push_back(t_env **begin_ll, char *var, char *content);

// error.c
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void *input);
int		quotes_error(void);

// free_mem.c
void	delete_lists(t_mshell *init);

#endif
