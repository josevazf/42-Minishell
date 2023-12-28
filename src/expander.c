/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by patatoss          #+#    #+#             */
/*   Updated: 2023/12/21 22:54:44 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	expander(t_mshell *init, char **envp)
{
	t_lexer	*head;
	int		i;
	int		len;
	
	head = init->lexer;
	i = 0;
	while (init->lexer)
	{
		if (init->lexer->str[0] == '$')
		{
			while (envp[i])
			{
				if (ft_strncmp(init->lexer->str + 1, envp[i], ft_strlen(init->lexer->str) - 1) == 0)
				{
					len = ft_strlen(init->lexer->str);
					free(init->lexer->str);
					init->lexer->str = ft_strndup(envp[i], len);
					return ;
				}
				i++;
			}
		}
		init->lexer = init->lexer->next;
	}
	init->lexer = head;
}
