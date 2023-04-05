/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:44:42 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/05 01:45:25 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *is_squote(t_token_list **tokens, char *line, t_tools *tools)
{
    int i;

    if (!line)
        return (NULL);
    i = 1;
	while (line[i] && line[i] != '\'')
		i++;
    if (line[i] && line[i] == '\'')
	    addback(tokens, ft_strndup(line + 1, i - 1), WORD);
    else
        tools->s_quote = 1;
	return (line + i + 1);
}

char	*is_dquote(t_token_list **tokens, char *line, t_tools *tools)
{
	int i;

    if (!line)
        return (NULL);
    i = 1;
	while (line[i] && line[i] != '\"' && line[i] != '$')
		i++;
    if (i == 1 && line[0] == 34 && line[1] != 34)
        tools->dollar_in = 1;
	if (line[i] == '$')
    {
	    addback(tokens, ft_strndup(line + 1, i - 1), WORD);
		return (line + i);
    }
    if (line[i] && line[i] == '\"')
	    addback(tokens, ft_strndup(line + 1, i - 1), WORD);
    else
        tools->d_quote = 1;
	return (line + i + 1);
}

char	*no_expand(t_token_list **tokens, char	*line, t_tools *tools)
{
	int i;
    int j;

    if (!line)
        return (NULL);
    i = 1;
    j = 0;
    // if (line && line[j] != 34 && line[j] != 32)
    // {
    //     while (line && line[j] != 34 && line[j] != 32)
    //         j++;
    //     addback(tokens, ft_strndup(line, j), WORD);
    //     return (line + j - 1);
    // }
	while (line[i] && line[i] != '\"')
		i++;
    if (line[i] && line[i] == '\"')
    {
	    addback(tokens, ft_strndup(line + 1, i - 1), WORD);
        line = no_expand(tokens, line + i + 1, tools); 
    }
    else
        tools->no_expand = 1;
	return (line + i + 1);
}