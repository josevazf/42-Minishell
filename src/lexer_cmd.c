/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:29:36 by jrocha-v          #+#    #+#             */
/*   Updated: 2023/12/13 11:59:46 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Find 'PATH=' in envp file and return the paths delimited by ':'
char	**parse_path(char **envp)
{
	char	*envp_dup;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	envp_dup = ft_strdup(envp[i] + 5);
	if (envp_dup == NULL)
		return (NULL);
	paths = ft_split(envp_dup, ':');
	free(envp_dup);
	if (paths == NULL)
		return (NULL);
	i = -1;
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
	if (ft_strcmp(cmd, "echo") == 0)
		ft_printf("builtin: echo-> %s\n", cmd);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_printf("builtin: cd-> %s\n", cmd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_printf("builtin: pwd-> %s\n", cmd);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_printf("builtin: export-> %s\n", cmd);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_printf("builtin: unset-> %s\n", cmd);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_printf("builtin: env-> %s\n", cmd);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_printf("builtin: exit-> %s\n", cmd);
	else
		ft_printf("shell cmd (%s)\n", cmd);
}

// TO UPDATEEEEE
void	find_cmd(t_lexer *tokens, char **envp)
{
	char	**paths;
	char	*cmd_path;

	paths = parse_path(envp);
	cmd_path = get_cmd_path(paths, tokens->input);
	if (cmd_path == NULL)
	{
		free(tokens->input);
		ft_free_smatrix(paths);
		free(cmd_path);
		ft_error(ft_strjoin("minishell: ", tokens->input), CMD_NOT_FOUND);
	}
	tokens->type = TYPE_CMD;
	tokens->path = cmd_path;
	cmd_router(tokens->input);
	ft_free_smatrix(paths);
	free(cmd_path);
}
