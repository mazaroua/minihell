/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/03/26 16:38:34 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	body(char *line)
{
	t_token_list	*tokens;
	t_cmd_line		*cmd_line;

	tokens = tokenizer(line);
	
	if (syntax(tokens))
	{
		cmd_line = parser(tokens);
	}
		// while (tokens)
		// {
		// 	printf("|%s|\n", tokens->value);
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

int main()
{
    char	*line;

    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);

		body(line);
    }
}