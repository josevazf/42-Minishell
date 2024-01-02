/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:08:41 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/02 23:36:38 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

# define BUILTIN_CMD 11
# define SHELL_CMD 12

typedef struct s_parser
{
	char			**cmd_exec;
	char			*path_exec;
	int				cmd_type;
	int				input;
	int				output;
	struct s_parser	*next;
}	t_parser;

// parser_main.c
t_parser	*create_parser_node(int cmd_type, char *cmd_temp, char *cmd_path);
void		parser_node_push_back(t_parser **begin_list, int cmd_type, char *cmd_temp, char *cmd_path);
void		parser_main(t_mshell *init);

// parser_cmd.c
//char	**parse_path(char **envp);
char	**parse_path(char *env_path);
char	*get_cmd_path(char **envp_paths, char *cmd);
char	*find_cmd(char *cmd);

#endif
