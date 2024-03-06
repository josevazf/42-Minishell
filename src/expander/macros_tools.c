/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:59:01 by tiago             #+#    #+#             */
/*   Updated: 2024/03/06 09:47:46 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node)
{
	init->exp->macro_len = 1;
	while (init->in[init->exp->i + init->exp->macro_len] && \
	!ft_iswhitespace(init->in[init->exp->i + \
	init->exp->macro_len]) && init->in[init->exp->i + \
	init->exp->macro_len] != '\"' \
	&& init->in[init->exp->i + init->exp->macro_len] != '\'' && \
	init->in[init->exp->i + init->exp->macro_len] != '$')
		init->exp->macro_len++;
	while (env_node && (strncmp(init->in + init->exp->i + 1, \
	env_node->var, init->exp->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != init->exp->macro_len - 1))
		env_node = env_node->next;
	return (env_node);
}

void	update_input(t_mshell *init)
{
	free(init->in);
	init->in = ft_strdup(init->exp->new_input);
	free(init->exp->new_input);
}

void	clear_macro(t_mshell *init)
{
	init->exp->new_input = ft_strldup(init->in, init->exp->i);
	init->exp->new_input = ft_strupdate(init->exp->new_input, \
	init->in + init->exp->i + init->exp->macro_len);
	update_input(init);
}

t_env	*macro_check_and_fetch(t_mshell *init, t_env *env_node)
{
	if (init->in[init->exp->i] == '\'' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 0;
	else if (init->in[init->exp->i] == '\'' && init->exp->s_quote == 0 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 1;
	else if (init->in[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->d_quote = 0;
	else if (init->in[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 0)
		init->exp->d_quote = 1;
	else if (init->in[init->exp->i] == '$' && init->in[init->exp->i \
	+ 1] && !ft_iswhitespace(init->in[init->exp->i + 1]) && init->\
	in[init->exp->i + 1] != '\"')
		env_node = fetch_macro(init, env_node);
	return (env_node);
}
