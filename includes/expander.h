/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/09 19:44:48 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

// expander.c
int		expand_aux(char *alph_exit_code);
void	expand(t_mshell *init, t_lexer *lex_nd, t_env *env_nd, int *exit_code);
void	expander(t_mshell *init, int *ext_cd, t_env *env_nd, t_lexer *lex_nd);

// macros_tools.c
void	update_input(t_mshell *init, t_lexer *lexer_node);
void	clear_macro(t_mshell *init, t_lexer *lexer_node);
t_env	*macro_check_fetch(t_mshell *init, t_env *env_nd, t_lexer *lexer_nd);
void	ignore_eof_macro(t_mshell *init, t_lexer *lexer_node);

// eof_handler.c
void	eof_manager(t_mshell *init);

// structs_init.c
void	expander_init(t_expand *expander);

#endif
