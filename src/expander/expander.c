/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                         		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 15:45:00 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		env_node = macro_check_and_fetch(init, env_node);
		if (init->in[init->exp->i] == '<' && init->in[init->exp->i + 1] == '<')
			ignore_eof_macro(init);
		else if (init->in[init->exp->i] == '$' && init->in[init->exp->i + 1] \
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
