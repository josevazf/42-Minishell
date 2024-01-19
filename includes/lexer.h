/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-v <jrocha-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:24:19 by tiaferna          #+#    #+#             */
/*   Updated: 2024/01/19 09:53:07 by jrocha-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../includes/minishell.h"
# include "../includes/expander.h"

# define CMD 1
# define PIPE 2
# define GREAT 3
# define DOU_GREAT 4
# define LESS 5
# define DOU_LESS 6

// lexer_main.c
void	lexer_router(t_lexer *tokens);
t_lexer	*lexer_list(char **args);
int 	lexer_main(t_mshell *init);

// lexer_split.c
int		lexer_size_of_word(char *s, size_t *i, t_mshell *init);
size_t	len_update(char *s, unsigned int start, size_t len);
char	*ft_lexer_substr(char *s, unsigned int start, size_t len);
void	create_token(t_mshell *init, size_t *i);
void	lexer_split(t_mshell *init);

// lexer_elements.c
void	lexer_elements_aid(char const *s, size_t *i);
int		lexer_elements(char const *s);

// lexer_quotes_checker.c
void	quotes_checker_aid(char const *s, int *i, int *count, char quote_type);
void	quotes_checker(char const *s);

// structs_init.c
void	lexer_init(t_lexer *lexer);

#endif
