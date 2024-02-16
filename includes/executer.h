/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/16 17:57:10 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../includes/minishell.h"

// executer_main.c
void	get_exit_code(int status, int *exit_code);
void	fork_pipe(t_mshell *init,t_parser *parser_node, char **strings_env, 
														int *exit_code);
void	fork_cmd(t_mshell *init,t_parser *parser_node, char **strings_env, 
														int *exit_code);
void	executer_fork_router(t_mshell *init, char **strings_env, int *exit_code, char ***envp_copy);
void	executer_main(t_mshell *init, int *exit_code, char ***envp_copy);

// executer_utils.c
void	fork_pipe_utils(int *pipe_fd, pid_t pid, int *exit_code, 
                                        t_parser **parser_node);
void	get_pipes(t_mshell *init);
char	**convert_env(t_mshell *init);
void	executer_cmd_router(t_mshell *init, t_parser *parser_node, 
							char **strings_env,	int *exit_code);

#endif
