/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/21 15:59:22 by tiago            ###   ########.fr       */
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

// executer_redirs.c
void	process_dev_urandom(void);
void	clean_here_doc(void);
void	process_here_doc(char **argv);
void	process_file(char *file_name, int file_type);

// executer_utils.c
void	get_pipes(t_mshell *init);
char	**convert_env(t_mshell *init);

#endif
