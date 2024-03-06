/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:43:34 by tiago             #+#    #+#             */
/*   Updated: 2024/03/06 09:48:38 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Makes a copy of the original envp */
char	**envp_dup(char **envp)
{
	int		i;
	char	**envp_copy;

	i = 0;
	while (envp[i])
		i++;
	envp_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

/* Updates de envp_copy variable to reflect any changes made to it */
char	**update_envp_copy(t_mshell *init, char ***envp_copy)
{
	int		i;
	t_env	*node;

	i = 0;
	node = init->env_table;
	while (node && i++ >= 0)
		node = node->next;
	ft_free_smatrix(*envp_copy);
	(*envp_copy) = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	node = init->env_table;
	while (++i >= 0 && node)
	{
		(*envp_copy)[i] = ft_strdup(node->var);
		if (node->visibility == 1 && node->var[ft_strlen(node->var) - 1] != '~')
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], "~");
		if (node->content)
		{
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], "=");
			(*envp_copy)[i] = ft_strupdate((*envp_copy)[i], node->content);
		}
		node = node->next;
	}
	(*envp_copy)[i] = NULL;
	return (*envp_copy);
}
