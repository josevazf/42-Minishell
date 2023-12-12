/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:29:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/12 15:51:44 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Find 'PATH=' in envp file and return the paths delimited by ':'
char	**parse_path(char **envp)
{
	char	*envp_dup;
	char	**paths;
	int		i;

	printf("test parse path: 1");
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	printf("test parse path: 2");
	envp_dup = ft_strdup(envp[i] + 5);
	if (envp_dup == NULL)
		return (NULL);
	paths = ft_split(envp_dup, ':');
	printf("test parse path: 3");
	free(envp_dup);
	if (paths == NULL)
		return (NULL);
	printf("test parse path: ok");
	return (paths);
}

// Get the full path for the command to execute
char	*get_cmd_path(char **envp_paths, char *cmd)
{
	char	*temp_path;
	char	*new_path;
	int		i;

	i = 0;
	while (envp_paths[++i])
	{
		temp_path = ft_strjoin(envp_paths[i], "/");
		if (temp_path == NULL)
			return (NULL);
		new_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (new_path == NULL)
			return (NULL);
		if (access(new_path, X_OK) == 0)
			return (new_path);
		free(new_path);
	}
	return (NULL);
}

void	cmd_router(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		ft_printf("test: echo->%s", cmd);
	else if (ft_strcmp(cmd, "cd"))
		ft_printf("test: cd->%s", cmd);
	else if (ft_strcmp(cmd, "pwd"))
		ft_printf("test: pwd->%s", cmd);
	else if (ft_strcmp(cmd, "export"))
		ft_printf("test: export->%s", cmd);
	else if (ft_strcmp(cmd, "unset"))
		ft_printf("test: unset->%s", cmd);
	else if (ft_strcmp(cmd, "env"))
		ft_printf("test: env->%s", cmd);
	else if (ft_strcmp(cmd, "exit"))
		ft_printf("test: exit->%s", cmd);
	else
		ft_printf("test: shell cmd");
}

// TO UPDATEEEEE
void	find_cmd(t_lexer *tokens, char **envp)
{
	char	**paths;
	char	*cmd_path;

	printf("%s", envp[2]);
	printf("test token: %s\n", tokens->input);
	paths = parse_path(envp);
	printf("test path: 1");
	cmd_path = get_cmd_path(paths, tokens->input);
	printf("test path: %s\n", cmd_path);
	if (cmd_path == NULL)
	{
		free(tokens->input);
		ft_free_smatrix(paths);
		free(cmd_path);
		ft_error(ft_strjoin("minishell: ", tokens->input), CMD_NOT_FOUND);
	}
	cmd_router(tokens->input);
	free(tokens->input);
	ft_free_smatrix(paths);
	free(cmd_path);
}

