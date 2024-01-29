/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:08:41 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/01/29 20:03:43 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

# define BUILTIN_CMD 11
# define SHELL_CMD 12

// parser_main.c
void		print_node(t_parser *parser); // TO DELETE EVENTUALLY
t_parser	*create_parser_node(t_mshell *init, char *cmds, char *cmd_path);
void		parser_node_push_back(t_mshell *init, t_parser **begin_list, char *cmds, char *cmd_path);
t_parser	*parser_node_router(t_mshell *init, t_parser *parser, char *redirs, char *cmds);
void		parser_main(t_mshell *init, t_parser *parser, char *redirs, char *cmds);

// parser_cmd.c
int			cmd_router(char *cmd);
char		**parse_path(char *env_path);
char		*get_cmd_path(char **envp_paths, char *cmd);
char		*find_cmd(char *cmd, t_mshell *init);

// parser_utils.c
char		*get_redirs(char *og_redirs, t_lexer **lexer);
char		*parser_merge_split(char *og_str, char *lexer_str);
void		free_parser_temps(char *cmds, char *redirs, char *cmd_path, char **cmd_full);
void		free_parser_vars(char **cmds, char **redirs);

// parser_redirs.c
void		process_dev_urandom(t_mshell *init);
void		clean_here_doc(void);
int			process_here_doc(t_mshell *init, char *eof);
int			process_file(t_mshell *init, char *file_name, int file_type);

// structs_init.c
void		parser_init(t_parser *parser);

#endif
