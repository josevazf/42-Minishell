/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/02 22:09:58 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

/**** 
	Também temos de expandir o caso: echo blablabla$USER 

****/

void	expander(t_mshell *init)
{
	t_lexer	*lexer_head;
	t_env	*env_head;
	
	lexer_head = init->lexer;
	env_head = init->env_table;
	while (init->lexer)
	{
		if (init->lexer->str[0] == '$')
		{
			init->env_table = env_head;
			while (init->env_table)
			{
				if (ft_strncmp(init->lexer->str + 1, init->env_table->var, \
				ft_strlen(init->lexer->str) - 1) == 0)
				{
					free(init->lexer->str);
					init->lexer->str = ft_strdup(init->env_table->content);
				}
				init->env_table = init->env_table->next;
			}
		}
		init->lexer = init->lexer->next;
	}
	init->lexer = lexer_head;
}
