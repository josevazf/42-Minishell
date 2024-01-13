/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/13 19:50:58 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node)
{
	init->expander->macro_len = 1;
	while (init->input[init->expander->i + init->expander->macro_len] && \
	!ft_iswhitespace(init->input[init->expander->i + \
	init->expander->macro_len]) && init->input[init->expander->i + \
	init->expander->macro_len] != '\"' && init->input[init->expander->i + \
	init->expander->macro_len] != '\'' && init->input[init->expander->i + \
	init->expander->macro_len] != '$')
		init->expander->macro_len++;
	while (env_node && (strncmp(init->input + init->expander->i + 1, \
	env_node->var, init->expander->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != init->expander->macro_len - 1))
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
	init->expander->new_input = ft_strldup(init->input, init->expander->i);
	init->expander->new_input = ft_strupdate(init->expander->new_input, init->input + init->expander->i + init->expander->macro_len);
	update_input(init);
}

void	expand(t_mshell *init, t_env *env_node)
{
	if (env_node == NULL && (init->input[init->expander->i] != '$' || init->input[init->expander->i + 1] != '?'  || init->expander->s_quote != 1))
				clear_macro(init);
	else
	{
		init->expander->new_input = ft_strldup(init->input, init->expander->i);
		if (init->input[init->expander->i] == '$' && init->input[init->expander->i + 1] == '?'  && init->expander->s_quote == 1)
			init->expander->new_input = ft_strupdate(init->expander->new_input, ft_itoa(init->exit_code));
		else
			init->expander->new_input = ft_strupdate(init->expander->new_input, env_node->content);
		init->expander->new_input = ft_strupdate(init->expander->new_input, init->input + init->expander->i + init->expander->macro_len);
		update_input(init);
	}
	init->expander->i = 0;
}

void	expander(t_mshell *init)
{
	t_env	*env_node;

	init->expander = (t_expand *)malloc(sizeof(t_expand));
	init->expander->i = 0;
	init->expander->s_quote = 1;
	while (init->input[init->expander->i])
	{
		env_node = init->env_table;
		if (init->input[init->expander->i] == '\'' && init->expander->s_quote == 1)
			init->expander->s_quote = 0;
		else if (init->input[init->expander->i] == '\'' && init->expander->s_quote == 0)
			init->expander->s_quote = 1;
		else if (init->input[init->expander->i] == '$' && init->expander->s_quote == 1)
			env_node = fetch_macro(init, env_node);
		if (init->input[init->expander->i] != '$' || (init->input[init->expander->i] == '$' && init->expander->s_quote == 0))
			init->expander->i++;
		else
			expand(init, env_node);
	}
}
