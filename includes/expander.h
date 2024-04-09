/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/09 17:31:05 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

// expander.c
void	expander(t_mshell *init, int *exit_code);

// macros_tools.c
void	update_input(t_mshell *init, t_lexer *lexer_node);
void	clear_macro(t_mshell *init, t_lexer *lexer_node);
t_env	*macro_check_and_fetch(t_mshell *init, t_env *env_node, t_lexer *lexer_node);
void	ignore_eof_macro(t_mshell *init, t_lexer *lexer_node);

// eof_handler.c
void	eof_manager(t_mshell *init);

// structs_init.c
void	expander_init(t_expand *expander);

#endif
