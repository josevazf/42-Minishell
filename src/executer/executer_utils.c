/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:05:37 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/20 15:25:57 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fork_pipe_utils(int *pipe_fd, pid_t pid, int *exit_code, 
											t_parser **parser_node)
{
	int	status;
	
	close(pipe_fd[1]);
	if (waitpid(pid, &status, 0) != -1 )
		get_exit_code(status, exit_code);
	else
	{
		perror("waitpid() failed yooo"); //corrigir
		exit(EXIT_FAILURE);
	}
	dup2(pipe_fd[0], (*parser_node)->input);
	close(pipe_fd[0]);
}

/* Get number of pipes */
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

/* Convert Env linked list to original format `**char` */
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
		temp_line = ft_strupdate(temp_line, "\t");
		env_table = env_table->next;
	}
	strings_env = ft_split(temp_line, '\t');
	free(temp_line);
	free(env_table);
	return (strings_env);
}

void	executer_cmd_router(t_mshell *init, t_parser *parser_node, char **strings_env, int *exit_code)
{
	if (!ft_strcmp(parser_node->cmd_exec[0], "echo"))
		echo(parser_node);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "cd"))
		cd(init, parser_node, exit_code);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "pwd"))
		pwd(parser_node);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "export"))
		export(init, strings_env);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "unset")) 
		unset(init, strings_env);
	else if (!ft_strcmp(parser_node->cmd_exec[0], "env")) 
		env(init);
	else
		execve(parser_node->path_exec, parser_node->cmd_exec, strings_env);
}