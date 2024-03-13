/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:08:41 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/03/13 16:29:11 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/minishell.h"

# define BUILTIN_CMD 11
# define SHELL_CMD 12

// parser_main.c
t_parser	*create_parser_node(t_mshell *init, char *cmds, t_parser *node);
void		parser_node_push_back(t_mshell *init, t_parser **begin_list, \
				char *cmds, t_parser *node);
t_parser	*parser_node_router(t_mshell *init, char ***envp_copy, \
				t_parser *parser, char *cmds);
int			check_pipe_syntax(t_mshell *init, t_lexer *lexer);
void		parser_main(t_mshell *init, char ***envp_copy, t_parser *parser, \
				char *cmds);

// parser_cmd.c
int			cmd_router(char *cmd);
char		**parse_path(char **env_path);
char		*get_cmd_path(char **envp_paths, char *cmd, char *tpath, \
				char *newpath);
char		*find_cmd(char *cmd, t_mshell *init, char ***envp_copy);

// parser_utils.c
int			check_redir_syntax(t_mshell *init);
char		*get_redirs(t_mshell *init, char *og_redirs, t_lexer **lexer);
char		*parser_merge_split(char *og_str, char *lexer_str);
void		free_parser_temps(char *cmds, char *redirs, char *cmd_path, \
				char **cmd_full);
void		free_parser_vars(char **cmds, char **redirs);

// structs_init.c
void		parser_init(t_parser *parser);

#endif
