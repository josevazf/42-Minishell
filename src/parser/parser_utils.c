/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/06 20:08:45 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Check if there is an unexpected token after a redirection (<, >, <<, >>) */
int	check_redir_syntax(t_mshell *init)
{
	t_lexer		*lexer;

	lexer = init->lexer;
	while (lexer)
	{
		if (lexer->operator == OUT_OWR || lexer->operator == OUT_APND || \
			lexer->operator == IN_READ || lexer->operator == IN_HDOC)
		{
			if (lexer->next->operator == PIPE || \
				lexer->next->operator == OUT_OWR || \
				lexer->next->operator == OUT_APND || \
				lexer->next->operator == IN_READ || \
				lexer->next->operator == IN_HDOC)
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					lexer->next->str);
				init->stop_exec = true;
				return (ERROR);
			}
		}
		lexer = lexer->next;
	}
	return (SUCCESS);
}

/* Merge redirs from one node into a single string */
char	*get_redirs(t_mshell *init, char *og_redirs, t_lexer **lexer)
{
	(void)init;
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
	if (cmds != NULL)
		free(cmds);
	if (redirs)
		free(redirs);
	if (cmd_path != NULL)
		free(cmd_path);
	if (cmd_full != NULL)
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
