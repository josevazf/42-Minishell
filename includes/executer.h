/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/11 20:02:00 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../includes/minishell.h"

// executer_main.c
void	get_exit_code(int status, int *exit_code);
void	executer_fork_router(t_mshell *init, char ***env, int *exit_code, \
			int i);
void	executer_main(t_mshell *init, char ***envp_copy, int *exit_code);

// executer_utils.c
void	write_here_doc(t_mshell *init, char *eof, int *pipe_fd, int *exit_code);
int		process_here_doc(t_mshell *init, char *eof, int *exit_code);
void	get_pipes(t_mshell *init);
void	exec_executable(t_mshell *init, t_parser *parser_node);
void	executer_cmd_router(t_mshell *init, t_parser *parser_node, \
			char ***strings_env, int *exit_code);

// executer_single_cmd.c
int		single_cmd_isdir(char *cmd);
int		single_cmd_notfound(t_mshell *init);
void	fork_single_cmd(t_mshell *init, t_parser *parser_node, \
			char ***strings_env, int *exit_code);
void	process_single_cmd(t_mshell *init, char ***strings_env, int *exit_code);
void	single_redirs_router(t_mshell *init, t_parser *node, int *exit_code);

// executer_multi_cmds.c
int		multi_cmd_isdir(t_mshell *init, char *cmd);
int		multi_cmd_notfound(t_mshell *init, t_parser *parser_node);
void	process_pipes(t_mshell *init);
void	process_child(t_mshell *init, t_parser *parser_node, \
									char ***strings_env, int *exit_code);
void	process_parent(t_mshell *init, int *exit_code);

// executer_multi_redirs.c
void	multi_check_input(t_mshell *init, t_parser *node, int i);
void	multi_check_output(t_mshell *init, t_parser *node, int i);
void	multi_redir_input(t_mshell *init, t_parser *node, int *exit_code);
void	multi_redir_output(t_mshell *init, t_parser *node);
void	multi_redirs_router(t_mshell *init, t_parser *node, int *exit_code);

// executer_multi_utils.c
void	close_parent_pipes(t_mshell *init);
void	close_redirs_pipes(t_mshell *init, t_parser *node);
void	close_child_pipes(t_mshell *init);
void	close_pipes(t_mshell *init, int i, int j);

// executer_redirs_utils.c
int		check_red_error(char *redir_syntax);
int		process_file(t_mshell *init, char *file_name, int file_type);

// executer_heredoc_expander.c
void	heredoc_expander(t_mshell *init, char **input, int *exit_code);

#endif
