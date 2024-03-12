/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:37:04 by guest             #+#    #+#             */
/*   Updated: 2024/03/11 17:02:34 by tiaferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	settle_eof(t_mshell *init, char *eof)
{
	init->expand_heredoc = true;
	if ((eof[0] == '\'' && eof[ft_strlen(eof) - 1] == '\'') || \
	(eof[0] == '\"' && eof[ft_strlen(eof) - 1] == '\"'))
	{
		if (eof[1] == '$' && eof[2] && eof[2] != '\'' && eof[2] != '\"')
			init->expand_heredoc = false;
		init->eof = ft_strldup(eof + 1, ft_strlen(eof) - 2);
	}
	else
		init->eof = ft_strdup(eof);
}

void	eof_manager(t_mshell *init)
{
	int		i;
	int		len;
	char	*old_str;
	char	*eof;

	i = 0;
	len = 0;
	old_str = ft_strdup(init->in);
	while (old_str[i])
	{
		if (old_str[i] == '<' && old_str[i + 1] == '<')
		{
			i += 2;
			while (old_str[i] && ft_iswhitespace(old_str[i]))
				i++;
			while (old_str[i + len] && !ft_iswhitespace(old_str[i + len]))
				len++;
			eof = ft_strldup(old_str + i, len);
			settle_eof(init, eof);
			free(eof);
			break ;
		}
		i++;
	}
	free(old_str);
}
