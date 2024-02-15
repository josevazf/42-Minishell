/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:44:11 by jrocha-v          #+#    #+#             */
/*   Updated: 2024/02/15 11:34:30 by tiaferna         ###   ########.fr       */
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
	char				*in;
	int					nbr_pipes;
	int					nbr_cmds;
	int					og_stdin;
	int					og_stdout;
	int					red_input;
	int					red_output;
	bool				cmd_not_found;
	bool				stop_redirs;
	bool				redirs_exist;
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
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_expand
{
	int		i;
	int		macro_len;
	int		s_quote;
	char	*new_input;
}	t_expand;

typedef struct s_parser
{
	char			**cmd_exec;
	char			*path_exec;
	int				cmd_type;
	int				input;
	int				output;
	struct s_parser	*next;
}	t_parser;

#endif
