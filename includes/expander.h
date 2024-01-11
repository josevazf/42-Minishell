/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 18:09:36 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/10 11:59:41 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "lexer.h"

typedef struct s_expand
{
	int		i;
	int		macro_len;
	int		s_quote;
	char	*new_input;
}	t_expand;

// expander.c
void	expander(t_mshell *init);

// structs_init.c
void	expander_init(t_expand *expander);

#endif
