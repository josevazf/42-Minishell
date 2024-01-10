/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patatoss <patatoss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:18:02 by patatoss          #+#    #+#             */
/*   Updated: 2024/01/07 17:18:17 by patatoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	quotes_checker_aid(char const *s, int *i, int *count, char quote_type)
{
	if (s[*i] == quote_type)
	{
		(*count)++;
		(*i)++;
		while (s[*i] != quote_type && s[*i])
			(*i)++;
		if (s[*i] && s[*i] == quote_type)
			(*count)++;
	}
}

void	quotes_checker(char const *s)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			quotes_checker_aid(s, &i, &s_quote, '\'');
		else if (s[i] == '\"')
			quotes_checker_aid(s, &i, &d_quote, '\"');
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		quotes_error();
	return ;
}
