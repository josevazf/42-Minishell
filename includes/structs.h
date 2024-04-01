/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:44:11 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/04/01 17:30:41 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../includes/minishell.h"
# include <stdbool.h>

typedef struct s_env
{
	char			*var;
	char			*content;
	int				visibility;
	struct s_env	*next;
}	t_env;

typedef struct s_mshell
{
	char				***envp_copy;
	char				*in;
	char				*origin_in;
	bool				set_var;
	char				**tcmd_full;
	char				*tcmd_path;
	char				*tredirs;
	char				*eof;
	char				**redirs;
	int					nbr_pipes;
	int					*child_pids;
	int					**pipe_fds;
	int					**closed_pipes;
	int					cmd_index;
	int					og_stdin;
	int					og_stdout;
	int					red_input;
	int					red_output;
	bool				expand_heredoc;
	bool				stop_exec;
	bool				is_echo;
	struct s_env		*env_table;
	struct s_expand		*exp;
	struct s_lexer		*lexer;
	struct s_parser		*parser;
}	t_mshell;

typedef struct s_lexer
{
	char			*str;
	int				operator;
	int				i;
	int				d_quote_expand;
	int				is_node;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_expand
{
	int		i;
	int		macro_len;
	int		s_quote;
	int		d_quote;
	char	*new_input;
}	t_expand;

typedef struct s_parser
{
	char			**cmd_exec;
	char			*path_exec;
	char			*redirs;
	bool			file_nf;
	bool			token_err;
	int				cmd_type;
	int				input_t;
	int				output_t;
	int				input;
	int				output;
	struct s_parser	*next;
}	t_parser;

#endif
