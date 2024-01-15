/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:26:40 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/15 17:15:50 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/executer.h"
#include "../includes/parser.h"

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

void simple_fork(t_mshell *init, char **envp)
{
	pid_t		pid;
	t_parser	*parser;
	
	parser = init->parser;
	pid = fork();
	if (pid == -1)
		ft_error("minishell: failed creating fork", ERROR);
	if (pid == 0)
		execve(parser->path_exec, parser->cmd_exec, envp);
	else
	{
		int status;
        if (waitpid(pid, &status, 0) != -1 )
		{
            if (WIFEXITED(status) )
                init->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status) )
                init->exit_code = WTERMSIG(status);
            else if (WIFSTOPPED(status) )
                init->exit_code = WSTOPSIG(status);
            else
                printf("Something strange just happened.\n");
        }
        else
		{
            perror("waitpid() failed");
            exit(EXIT_FAILURE);
        }
	}
}

void	executer_main(t_mshell *init, char **envp)
{
	//int			i;
	char		**strings_env;
	
	//i = -1;
	strings_env = convert_env(init);
	simple_fork(init, envp);
/* 	while (strings_env[++i])
		ft_printf("%s", strings_env[i]); */
	ft_free_smatrix(strings_env);
}
