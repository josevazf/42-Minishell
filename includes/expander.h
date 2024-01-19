/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 10:04:13 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "../includes/minishell.h"

// expander.c
void	expander(t_mshell *init);

// structs_init.c
void	expander_init(t_expand *expander);

#endif
