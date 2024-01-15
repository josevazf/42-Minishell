/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/12 15:51:21 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"

void	get_pipes(t_mshell *init)
{
	t_lexer	*lexer;
	
	init->nbr_cmds = 0;
	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == PIPE)
			init->nbr_pipes++;
		lexer = lexer->next;
	}
	free(lexer);
}

/* Convert Env linked list to original format `**char` 
	TO FIXXX */
char	**convert_env(t_mshell *init)
{
	char	**strings_env;
	char	*temp_line;
	char	*temp_line2;
	char	*temp_line3;
	char	*temp_line4;
	t_env	*env_table;

	env_table = init->env_table;
	temp_line = ft_strdup("");
	while (env_table)
	{
		temp_line4 = ft_strjoin(temp_line, env_table->var);
		free(temp_line);
		temp_line3 = ft_strjoin(temp_line4, "=");
		free(temp_line4);
		temp_line2 = ft_strjoin(temp_line3, env_table->content);
		free(temp_line3);
		temp_line = ft_strjoin(temp_line2, "\n\t");
		free(temp_line2);
		env_table = env_table->next;
	}
	strings_env = ft_split(temp_line, '\t');
	free(temp_line);
	free(env_table);
	return (strings_env);
}