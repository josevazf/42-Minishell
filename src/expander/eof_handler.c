/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:37:04 by guest             #+#    #+#             */
/*   Updated: 2024/02/07 12:46:22 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    eof_protector(t_mshell *init, int *i, int *len, char *old_str)
{
    char    *eof;

    eof = ft_strldup(old_str + *i, *len);
    free(init->in);
    init->in = ft_strldup(old_str, *i);
    init->in = ft_strupdate(init->in, "\'");
    init->in = ft_strupdate(init->in, eof);
    init->in = ft_strupdate(init->in, "\'");
    init->in = ft_strupdate(init->in, old_str + *i + *len);
    free(eof);
}

void    eof_manager(t_mshell *init)
{
    int     i;
    int     len;
    char    *old_str;

    i = 0;
    len = 0;
    old_str = ft_strdup(init->in);
    while(old_str[i])
    {
        if (old_str[i] == '<' && old_str[i + 1] == '<')
        {
            i += 2;
            while (old_str[i] && ft_iswhitespace(old_str[i]))
                i++;
            while (old_str[i + len] && !ft_iswhitespace(old_str[i + len]))
                len++;
            if (old_str[i])
            {
                eof_protector(init, &i, &len, old_str);
                break ;
            }
        }
        i++;
    }
    printf("****%s****\n", init->in);
    free(old_str);
}
