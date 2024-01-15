/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/12 16:29:12 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "parser.h"

// executer_main.c
void	fork_pipe(t_parser *parser_node, char **envp);
void 	fork_simple(t_mshell *init, char **envp);
void	fork_router(t_mshell *init, char **envp);
void	executer_main(t_mshell *init, char **envp);

// executer_utils.c
void	get_pipes(t_mshell *init);
char	**convert_env(t_mshell *init);

#endif
