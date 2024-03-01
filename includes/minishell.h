/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:49:31 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/01 19:32:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "../includes/structs.h"
# include "../includes/lexer.h"
# include "../includes/expander.h"
# include "../includes/parser.h"
# include "../includes/executer.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define ERROR 1
# define SUCCESS 0
# define CMD_NOT_FOUND 127
# define IN_FILE 0
# define IN_HD 1
# define OUT_FOWR 2
# define OUT_FAPND 3
# define IO_PIPE 4
# define NO_RED 5
# define INVALID 6

extern int	g_signo;
// minishell.c
/*---- main ----*/

// structs_init.c
void	env_table_init(t_env *env_table);
void	mshell_init(t_mshell *init);

// env_main.c
char	**envp_dup(char **envp);
char	**update_envp_copy(t_mshell *init, char ***envp_copy);
void	env_node_push_back(t_env *begin_list, char *var, char *content);
t_env	*create_env_node(char *var, char *content);
int		*create_env_list(t_mshell *init, char **envp_copy);

// error.c
int     file_error(char *file_name);
int     redirs_error(void);
int		args_error(void);
int		fd_error(int fd);
int		fork_error(int fd);
int		malloc_error(void *input);
int		quotes_error(void);

// free_mem.c
void	free_expander(t_expand *expander);
void	free_parser(t_parser *parser);
void	free_env(t_env *env);
void	free_lexer(t_lexer *lexer);
void	delete_lists(t_mshell *init);

// builtins
void	pwd(t_parser *parser);
void	cd(t_mshell *init, t_parser *parser, int *exit_code, char ***envp_copy);
void	env(t_mshell *init);
void	echo(t_parser *parser, int i, int j);
void	export(t_mshell *init, char ***envp_copy, int *exit_code);
void	unset(t_mshell *init, char ***envp_copy);

// new_var_set.c
int		new_var_checker(t_mshell *init, char ***envp_copy);

// export_utils.c
t_env	*assign_val(t_env **count, int *flag, t_mshell *init);
void	save_in_stash(t_env *node, t_env *stash);
int		check_stash(t_env *node, t_env *stash);
void	sort_list(t_env **prnt, t_env *env_node, t_mshell *init, t_env *stash);
void	check_oldpwd(t_env *prnt, int *flag);

// exit_shell.c
void	exit_ms(t_mshell *init);

// signals.c
void	sigint_handler(int sig);
void	sighandler_fork(int signo);
void	set_signals();

// print_utils.c
void	print_parser(t_mshell *init);
void	print_lexer(t_mshell *init);
void	print_env(t_mshell *init);

#endif
