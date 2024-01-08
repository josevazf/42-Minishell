/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:24 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/08 18:59:59 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* Helper function to shorten 'parser_main' */
char	*get_cmd_temp(char *cmd_temp, char *cmd_temp2, char *str)
{
	cmd_temp = ft_strjoin(cmd_temp2, str);
	free(cmd_temp2);	
	return (cmd_temp);
}

/* Helper function to shorten 'parser_main' */
char	*get_cmd_temp2(char *cmd_temp, char *cmd_temp2)
{
	cmd_temp2 = ft_strjoin(cmd_temp, "\n");
	free(cmd_temp);	
	return (cmd_temp2);
}
