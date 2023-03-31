/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:54:41 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/31 17:56:48 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void free_node(t_token_list **tokens)
// {
// 	t_token_list *head;
// 	head = *tokens;
// 	if(!head->next)
// 		free_node(&head->next);
// 	free(head);
// }

t_token_list *tokenizer(char *line, int *i)
{
	t_token_list	*tokens;
	t_tools			tools;

	tokens = NULL;
    while (*line)
    {
        if (ft_strchr(" \t\v\f\r", *line))
            line = is_wspace(&tokens, line);
        else if (ft_strchr("><", *line))
            line = is_redirections(&tokens, line);
        else if (ft_strchr("$|", *line))
            line = is_dollar_pipe(&tokens, line);
        else if (ft_strchr("\'", *line))
		{
            line = is_squote(&tokens, line, i, &tools);
			if (*i == 1)
				break;
		}
		else if (ft_strchr("\"", *line))
		{
			line = is_dquote(&tokens, line, i, &tools);
			while (!ft_strncmp(line, "$$", 2))
			{
				line = is_dollar_pipe(&tokens, line);
				tools.after_variable = 1;
			}
			if (*line == '$')
				line = afdollar(&tokens, line, &tools);
			if (*i == 1)
				break;
		}
        else
		{
            line = is_word(&tokens, line);
		}
    }
	addback(&tokens, "N", NLINE);
	return(tokens);
}
