/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/10 09:08:15 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
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
	char			*input;
	int				nbr_pipes;
	int				nbr_cmds;
	struct s_env	*env_table;
	struct s_expand	*expander;
	struct s_lexer	*lexer;
	struct s_parser	*parser;
}	t_mshell;

// minishell.c
/*---- main ----*/

// env_main.c
void	env_node_push_back(t_env **begin_ll, char *var, char *content);
t_env	*create_env_node(char *var, char *content);
int		*create_env_list(t_mshell *init, char **envp, int i);

// error.c
int		args_error(void);
int		fd_error(int fd);
int		malloc_error(void *input);
int		quotes_error(void);

// free_mem.c
void	free_parser(t_mshell *init);
void	free_env(t_mshell *init);
void	free_lexer(t_mshell *init);
void	delete_lists(t_mshell *init);

// pwd.c
void	pwd(t_mshell *init);

// cd.c
void	cd(t_mshell *init);

// env.c
void	env(t_mshell *init);

// echo.c
void	echo(t_mshell *init);

// export.c
void	export(t_mshell *init);

// print_utils.c
void	print_parser(t_mshell *init);
void	print_lexer(t_mshell *init);
void	print_env(t_mshell *init);

#endif
