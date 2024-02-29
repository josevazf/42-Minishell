/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2024/02/29 22:27:29 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../includes/minishell.h"

// OPERATORS
# define CMD 1
# define PIPE 2
# define OUT_OWR 3
# define OUT_APND 4
# define IN_READ 5
# define IN_HDOC 6

// lexer_main.c
void	lexer_router(t_lexer *tokens);
int		lexer_main(t_mshell *init, char **envp_copy, int *exit_code);

// lexer_split.c
void	lexer_split(t_mshell *init);

// lexer_split_utils.c
int		lexer_size_of_word(char *s, size_t *i, t_mshell *init);
size_t	len_update(char *s, unsigned int start, size_t len);
char	*ft_lexer_substr(char *s, unsigned int start, size_t len);

// lexer_elements.c
void	lexer_elements_aid(char const *s, size_t *i);
int		lexer_elements(char const *s);

// lexer_quotes_checker.c
void	quotes_checker_aid(char const *s, int *i, int *count, char quote_type);
int		quotes_checker(char const *s);

// structs_init.c
void	lexer_init(t_lexer *lexer);

#endif
