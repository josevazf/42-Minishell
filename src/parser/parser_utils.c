/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/05 11:57:49 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_redirs(char *og_redirs, t_lexer **lexer)
{
	if (!og_redirs)
	{
		og_redirs = ft_strdup((*lexer)->str);
		if ((*lexer)->next == NULL)
			return (og_redirs);
		(*lexer) = (*lexer)->next;
		og_redirs = parser_merge_split(og_redirs, (*lexer)->str);
	}
	else
	{
		og_redirs = ft_strupdate(og_redirs, (*lexer)->str);
		if ((*lexer)->next == NULL)
			return (og_redirs);
		(*lexer) = (*lexer)->next;
		og_redirs = parser_merge_split(og_redirs, (*lexer)->str);
	}
	return (og_redirs);
}

char	*parser_merge_split(char *og_str, char *lexer_str)
{
	og_str = ft_strupdate(og_str, "\t");
	og_str = ft_strupdate(og_str, lexer_str);
	og_str = ft_strupdate(og_str, "\t");
	return (og_str);
}

/* Helper function to free Parser variables */
void	free_parser_temps(char *cmds, char *redirs, char *cmd_path, 
												char **cmd_full)
{
	if (cmds)
		free(cmds);
	if (redirs)
		free(redirs);
	if (cmd_path)
		free(cmd_path);
	if (cmd_full)
		ft_free_smatrix(cmd_full);
}

/* Helper function to free Parser variables */
void	free_parser_vars(char **cmds, char **redirs)
{
	*cmds = NULL;
	*redirs = NULL;
	free(*cmds);
	free(*redirs);
}
