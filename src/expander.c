/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/10 09:47:00 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node)
{
	init->expander->macro_len = 0;
	while (init->input[init->expander->i + init->expander->macro_len] && !ft_iswhitespace(init->input[init->expander->i + init->expander->macro_len]) && init->input[init->expander->i + init->expander->macro_len] != '\"')
		init->expander->macro_len++;
	while (env_node && (strncmp(init->input + init->expander->i + 1, env_node->var, init->expander->macro_len - 1) != 0 || (int)ft_strlen(env_node->var) != init->expander->macro_len - 1))
		env_node = env_node->next;
	return (env_node);
}

void	update_input(t_mshell *init)
{
	free(init->input);
	init->input = ft_strdup(init->expander->new_input);
	free(init->expander->new_input);
}

void	clear_macro(t_mshell *init)
{
	init->expander->new_input = (char *)malloc(sizeof(char) * (ft_strlen(init->input) - init->expander->macro_len) + 1);
	ft_memset(init->expander->new_input, 'x', ft_strlen(init->input) - init->expander->macro_len);
	ft_memcpy(init->expander->new_input, init->input, init->expander->i);
	ft_memcpy(init->expander->new_input + init->expander->i, init->input + init->expander->i + init->expander->macro_len, ft_strlen(init->expander->new_input));
	update_input(init);
}

void	expand(t_mshell *init, t_env *env_node)
{
	init->expander->new_input = malloc(sizeof(char) * (ft_strlen(init->input) - init->expander->macro_len + ft_strlen(env_node->content)) + 1);
	ft_memset(init->expander->new_input, 'x', ft_strlen(init->input) - init->expander->macro_len + ft_strlen(env_node->content) + 1);
	ft_memcpy(init->expander->new_input, init->input, init->expander->i);
	ft_memcpy(init->expander->new_input + init->expander->i, env_node->content, ft_strlen(env_node->content));
	ft_memcpy(init->expander->new_input + init->expander->i + ft_strlen(env_node->content), init->input + init->expander->i + init->expander->macro_len, ft_strlen(init->expander->new_input));
	update_input(init);
	init->expander->i = 0;
}

void	expander(t_mshell *init)
{
	t_env	*env_node;

	init->expander->i = 0;
	init->expander->s_quote = 1;
	while (init->input[init->expander->i])
	{
		env_node = init->env_table;
		if (init->input[init->expander->i] == '\'' && init->expander->s_quote == 1)
			init->expander->s_quote = 0;
		else if (init->input[init->expander->i] == '\'' && init->expander->s_quote == 0)
			init->expander->s_quote = 1;
		if (init->input[init->expander->i] == '$' && init->expander->s_quote == 1)
		{
			env_node = fetch_macro(init, env_node);
			if (env_node == NULL)
				clear_macro(init);
		}
		if (init->input[init->expander->i] != '$' || (init->input[init->expander->i] == '$' && init->expander->s_quote == 0))
			init->expander->i++;
		else
			expand(init, env_node);
	}
	ft_printf("expanded to: %s\n", init->input);
}
