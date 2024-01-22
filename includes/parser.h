/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:08:41 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/19 16:06:01 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

# define BUILTIN_CMD 11
# define SHELL_CMD 12

// parser_main.c
void		print_node(t_parser *parser); // TO DELETE EVENTUALLY
t_parser	*create_parser_node(int cmd_type, char *cmd_temp, char *cmd_path);
void		parser_node_push_back(t_parser **begin_list, int cmd_type, \
											char *cmd_temp, char *cmd_path);
void		parser_main(t_mshell *init, t_lexer *lexer, t_parser *parser, \
																int cmd_type);

// parser_cmd.c
//char	**parse_path(char **envp);
int			cmd_router(char *cmd);
char		**parse_path(char *env_path);
char		*get_cmd_path(char **envp_paths, char *cmd);
char		*find_cmd(char *cmd, t_mshell *init);

// parser_utils.c
void		free_parser_temps(char *cmd_path, char *cmd_temp);

// structs_init.c
void		parser_init(t_parser *parser);

#endif
