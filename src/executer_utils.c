/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 09:55:23 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/lexer.h"

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
	t_env	*env_table;

	env_table = init->env_table;
	temp_line = ft_strdup("");
	while (env_table)
	{
		temp_line = ft_strupdate(temp_line, env_table->var);
		temp_line = ft_strupdate(temp_line, "=");
		temp_line = ft_strupdate(temp_line, env_table->content);
		temp_line = ft_strupdate(temp_line, "\n\t");
		env_table = env_table->next;
	}
	strings_env = ft_split(temp_line, '\t');
	free(temp_line);
	free(env_table);
	return (strings_env);
}

/* void	executer_router()
{
	if (ft_strcmp(cmd, "echo") == 0)
		 
	else if (ft_strcmp(cmd, "cd") == 0)
		
	else if (ft_strcmp(cmd, "pwd") == 0)
		
	else if (ft_strcmp(cmd, "export") == 0)
		
	else if (ft_strcmp(cmd, "unset") == 0) 
		
	else if (ft_strcmp(cmd, "env") == 0) 
		
	else if (ft_strcmp(cmd, "exit") == 0)
		
	else
		execve(parser_node->path_exec, parser_node->cmd_exec, envp);
} */
