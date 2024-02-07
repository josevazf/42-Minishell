/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                         		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 15:45:00 by tiago            ###   ########.fr       */
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

void	expand(t_mshell *init, t_env *env_node, int *exit_code)
{
	char		*i_inp;
	t_expand	*i_exp;
	char		*alph_exit_code;

	i_inp = init->in;
	i_exp = init->exp;
	alph_exit_code = ft_itoa(*exit_code);
	if (env_node == NULL && (i_inp[i_exp->i] != '$' || \
	i_inp[i_exp->i + 1] != '?' || i_exp->s_quote != 1))
		clear_macro(init);
	else
	{
		i_exp->new_input = ft_strldup(i_inp, i_exp->i);
		if (i_inp[i_exp->i] == '$' && i_inp[i_exp->i + 1] == '?' \
		&& i_exp->s_quote == 1)
			i_exp->new_input = ft_strupdate(i_exp->new_input, alph_exit_code);
		else
			i_exp->new_input = ft_strupdate(i_exp->new_input, \
			env_node->content);
		i_exp->new_input = ft_strupdate(i_exp->new_input, \
		i_inp + i_exp->i + i_exp->macro_len);
		update_input(init);
	}
	free(alph_exit_code);
	i_exp->i = 0;
}

void	expander(t_mshell *init, int *exit_code)
{
	t_env	*env_node;

	init->exp = (t_expand *)malloc(sizeof(t_expand));
	expander_init(init->exp);
	while (init->in[init->exp->i])
	{
		env_node = init->env_table;
		if (init->in[init->exp->i] == '\'' && init->exp->s_quote == 1)
			init->exp->s_quote = 0;
		else if (init->in[init->exp->i] == '\'' && init->exp->s_quote == 0)
			init->exp->s_quote = 1;
		else if (init->in[init->exp->i] == '$' && init->in[init->exp->i \
		+ 1] && !ft_iswhitespace(init->in[init->exp->i + 1]) && init->\
		in[init->exp->i + 1] != '\"' && init->exp->s_quote == 1)
			env_node = fetch_macro(init, env_node);
		if (init->in[init->exp->i] == '$' && init->in[init->exp->i + 1] \
		&& (ft_iswhitespace(init->in[init->exp->i + 1]) || \
		init->in[init->exp->i + 1] == '\"') && init->exp->s_quote == 1)
			init->exp->i++;
		else if (init->in[init->exp->i] != '$' || (init->in[init->exp->i] == \
		'$' && init->exp->s_quote == 0))
			init->exp->i++;
		else
			expand(init, env_node, exit_code);
	}
}
