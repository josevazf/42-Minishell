/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/05 15:54:30 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "../includes/minishell.h"

// executer_main.c
void	get_exit_code(int status, int *exit_code);
void	fork_pipe(t_parser *parser_node, char **envp, int *exit_code);
void	fork_cmd(t_parser *parser_node, char **envp, int *exit_code);
void	executer_router(t_mshell *init, char **envp, int *exit_code);
void	executer_main(t_mshell *init, char **envp, int *exit_code);

// executer_utils.c
void	fork_pipe_utils(int *pipe_fd, pid_t pid, int *exit_code, 
                                        t_parser **parser_node);
void	get_pipes(t_mshell *init);
char	**convert_env(t_mshell *init);

#endif
