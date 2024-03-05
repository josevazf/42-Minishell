/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/03/05 00:16:39 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../includes/minishell.h"

// expander.c
void	expander(t_mshell *init, int *exit_code);

// macros_tools.c
void	update_input(t_mshell *init);
void	clear_macro(t_mshell *init);
t_env	*macro_check_and_fetch(t_mshell *init, t_env *env_node);

// eof_handler.c
void	eof_manager(t_mshell *init);

// structs_init.c
void	expander_init(t_expand *expander);

#endif
