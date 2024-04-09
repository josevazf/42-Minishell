/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 23:59:01 by tiaferna          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:02 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*fetch_macro(t_mshell *init, t_env *env_node, t_lexer *lexer_node)
{
	init->exp->macro_len = 1;
	while (lexer_node->str[init->exp->i + init->exp->macro_len] && \
	!ft_iswhitespace(lexer_node->str[init->exp->i + \
	init->exp->macro_len]) && lexer_node->str[init->exp->i + \
	init->exp->macro_len] != '\"' \
	&& lexer_node->str[init->exp->i + init->exp->macro_len] != '\'' && \
	lexer_node->str[init->exp->i + init->exp->macro_len] != '$')
		init->exp->macro_len++;
	while (env_node && (ft_strncmp(lexer_node->str + init->exp->i + 1, \
	env_node->var, init->exp->macro_len - 1) != 0 || \
	(int)ft_strlen(env_node->var) != init->exp->macro_len - 1))
		env_node = env_node->next;
	init->exp->d_quote = 1;
	return (env_node);
}

void	update_input(t_mshell *init, t_lexer *lexer_node)
{
	free(lexer_node->str);
	lexer_node->str = ft_strdup(init->exp->new_input);
	free(init->exp->new_input);
}

void	clear_macro(t_mshell *init, t_lexer *lexer_node)
{
	init->exp->new_input = ft_strldup(lexer_node->str, init->exp->i);
	init->exp->new_input = ft_strupdate(init->exp->new_input, \
	lexer_node->str + init->exp->i + init->exp->macro_len);
	update_input(init, lexer_node);
}

t_env	*macro_check_and_fetch(t_mshell *init, t_env *env_node, t_lexer *lexer_node)
{
	if (lexer_node->str[init->exp->i] == '\'' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 0;
	else if (lexer_node->str[init->exp->i] == '\'' && init->exp->s_quote == 0 \
	&& init->exp->d_quote == 1)
		init->exp->s_quote = 1;
	else if (lexer_node->str[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 1)
		init->exp->d_quote = 0;
	else if (lexer_node->str[init->exp->i] == '\"' && init->exp->s_quote == 1 \
	&& init->exp->d_quote == 0)
		init->exp->d_quote = 1;
	else if (lexer_node->str[init->exp->i] == '$' && lexer_node->str[init->exp->i \
	+ 1] && !ft_iswhitespace(lexer_node->str[init->exp->i + 1]) && init->\
	in[init->exp->i + 1] != '\"')
		env_node = fetch_macro(init, env_node, lexer_node);
	return (env_node);
}

void	ignore_eof_macro(t_mshell *init, t_lexer *lexer_node)
{
	init->exp->i += 2;
	while (lexer_node->str[init->exp->i] && \
	ft_iswhitespace(lexer_node->str[init->exp->i]))
		init->exp->i++;
	while (lexer_node->str[init->exp->i] && \
	!ft_iswhitespace(lexer_node->str[init->exp->i]) && \
	(lexer_node->str[init->exp->i] != '\'' || lexer_node->str[init->exp->i] != '\"'))
		init->exp->i++;
}
