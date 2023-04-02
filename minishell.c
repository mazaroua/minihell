/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:26:43 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/02 16:04:25 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	body(char *line, char **env)
{
	t_token_list	*tokens;
	t_cmd_line		*cmd_line;
	t_env_list		*env_list;
	int				i;

	tokens = tokenizer(line, &i);
	cmd_line = NULL;
	env_list = NULL;
	if (syntax(tokens) && i != 1)
	{
		env_vars_list(&env_list, env);
		expand(&tokens, &env_list);
		parser(&cmd_line, tokens);
	}
		//////////////////////////////////////////////
		int j = 0;
		while (cmd_line->str[j])
			printf("%s\n", cmd_line->str[j++]);
		if (cmd_line->redirections)
			printf("%d %s\n", cmd_line->redirections->type, cmd_line->redirections->file);
		puts("--------");
		if (cmd_line->next)
		{
			j = 0;
			while (cmd_line->next->str[j])
			printf("%s\n", cmd_line->next->str[j++]);
			if (cmd_line->next->redirections)
				printf("%d %s\n", cmd_line->next->redirections->type, cmd_line->next->redirections->file);

		}
		///////////////////////////////////////////////
	
	
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
	
    char	*line;
    while (1)
    {
		line = prompt();
		if (!ft_strcmp(line, "exit"))
			exit(0);
		if (line)
			body(line, env);
    }
}