/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:13:08 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/08 16:19:22 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_home_var(t_env_list **env_list)
{
    t_env_list	*envlist;
	char		*home;

	envlist = *env_list;
	while (envlist)
	{
		if (!ft_strcmp(envlist->name, "HOME"))
		{
			home = envlist->value;
			return (home);
		}
		envlist = envlist->next;
	}
	return (home);
}