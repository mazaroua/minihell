/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/31 17:00:09 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_token_list **tokens)
{
	t_token_list	*token;

	token = *tokens;
	while (token->type != NLINE)
	{
		if (token->type == AFDOLLAR)
		{
			token->value = getenv(token->value);
			// token->type = WORD;
		}
		token = token->next;
	}
}

void	body(char *line)
{
	t_token_list	*tokens;

	tokens = tokenizer(line);
	expand(&tokens);
	t_cmd_line		*cmd_line = NULL;
	if (syntax(tokens))
	{
		parser(cmd_line, tokens);
	}
	
	
	// while (tokens)
	// {
	// 	printf("|%s| ", tokens->value);
	// 	printf("|%d|\n", tokens->type);
	// 	tokens = tokens->next;
	// }
}

char    *prompt(void)
{
    char	*line;

	line = readline("\x1B[36m""minishell$ ""\001\e[0m\002");
	add_history(line);
	line = remove_additional_spaces(line);
    return (line);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	
    char	*line;

    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);
		body(line);
    }
}