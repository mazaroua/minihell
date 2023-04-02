/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 00:26:22 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/02 00:27:00 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(t_token_list **tokens, t_env_list **env)
{
	t_token_list	*token;
	t_env_list		*envlist;

	if (!*tokens || (*tokens)->type == NLINE)
		return ;
	envlist = *env;
	token = *tokens;
	while (token->type != NLINE)
	{
		if (token->type == AFDOLLAR)
		{
			while (envlist)
			{
				if (!ft_strcmp(token->value, envlist->name))
					token->value = envlist->value;
				envlist = envlist->next;
			}
		}
		token = token->next;
	}
}

t_env_list	*add_var(char *name, char *value)
{
	t_env_list	*env_var;

	env_var = malloc(sizeof(t_env_list));
	env_var->name = name;
	env_var->value = value;
	env_var->next = NULL;
	return (env_var);
}

void	fill_env_list(t_env_list **env_list, t_env_list *new)
{
	t_env_list	*curr;

	curr = *env_list;
	if (!*env_list)
		*env_list = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	env_vars_list(t_env_list **env_list, char **env)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		fill_env_list(env_list, add_var(str[0], str[1]));
		i++;
	}
}