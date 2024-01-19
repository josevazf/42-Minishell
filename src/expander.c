/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:57:05 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 15:24:41 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node)
{
	I->EXP->macro_len = 1;
	while (I->INP[I->EXP->i + I->EXP->macro_len] && \
	!ft_iswhitespace(I->INP[I->EXP->i + \
	I->EXP->macro_len]) && I->INP[I->EXP->i + I->EXP->macro_len] != '\"' \
	&& I->INP[I->EXP->i + I->EXP->macro_len] != '\'' && \
	I->INP[I->EXP->i + I->EXP->macro_len] != '$')
		I->EXP->macro_len++;
	while (env_node && (strncmp(I->INP + I->EXP->i + 1, \
	env_node->var, I->EXP->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != I->EXP->macro_len - 1))
		env_node = env_node->next;
	return (env_node);
}

void	update_input(t_mshell *init)
{
	free(I->INP);
	I->INP = ft_strdup(I->EXP->new_input);
	free(I->EXP->new_input);
}

void	clear_macro(t_mshell *init)
{
	I->EXP->new_input = ft_strldup(I->INP, I->EXP->i);
	I->EXP->new_input = ft_strupdate(I->EXP->new_input, \
	I->INP + I->EXP->i + I->EXP->macro_len);
	update_input(init);
}

void	expand(t_mshell *init, t_env *env_node)
{
	char		*i_inp;
	t_expand	*i_exp;

	i_inp = init->input;
	i_exp = init->expander;
	if (env_node == NULL && (i_inp[i_exp->i] != '$' || \
	i_inp[i_exp->i + 1] != '?' || i_exp->s_quote != 1))
		clear_macro(init);
	else
	{
		i_exp->new_input = ft_strldup(i_inp, i_exp->i);
		if (i_inp[i_exp->i] == '$' && i_inp[i_exp->i + 1] == '?' \
		&& i_exp->s_quote == 1)
			i_exp->new_input = ft_strupdate(i_exp->new_input, \
			ft_itoa(exit_code));
		else
			i_exp->new_input = ft_strupdate(i_exp->new_input, \
			env_node->content);
		i_exp->new_input = ft_strupdate(i_exp->new_input, \
		i_inp + i_exp->i + i_exp->macro_len);
		update_input(init);
	}
	i_exp->i = 0;
}

void	expander(t_mshell *init)
{
	t_env	*env_node;

	I->EXP = (t_expand *)malloc(sizeof(t_expand));
	expander_init(I->EXP);
	while (I->INP[I->EXP->i])
	{
		env_node = init->env_table;
		if (I->INP[I->EXP->i] == '\'' && I->EXP->s_quote == 1)
			I->EXP->s_quote = 0;
		else if (I->INP[I->EXP->i] == '\'' && I->EXP->s_quote == 0)
			I->EXP->s_quote = 1;
		else if (I->INP[I->EXP->i] == '$' && I->INP[I->EXP->i + 1] && \
		!ft_iswhitespace(I->INP[I->EXP->i + 1]) && init->\
		input[I->EXP->i + 1] != '\"' && I->EXP->s_quote == 1)
			env_node = fetch_macro(init, env_node);
		if (I->INP[I->EXP->i] == '$' && I->INP[I->EXP->i + 1] && \
		(ft_iswhitespace(I->INP[I->EXP->i + 1]) || I->INP[I->EXP->i \
		+ 1] == '\"') && I->EXP->s_quote == 1)
			I->EXP->i++;
		else if (I->INP[I->EXP->i] != '$' || (I->INP[I->EXP->i] == '$' \
		&& I->EXP->s_quote == 0))
			I->EXP->i++;
		else
			expand(init, env_node);
	}
}
