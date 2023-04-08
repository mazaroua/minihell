/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:09:06 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/08 16:27:10 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(char *path, t_env_list **env_list)
{
    int i;

    if (path == NULL || path[0] == '~')
    {
        char *home_dir = get_home_var(env_list);
        if (!home_dir)
        {
            perror("Error: HOME directory not found");
            return;
        }
        i = chdir(home_dir);
    }
    else
         i = chdir(path);
    if (i != 0)
        perror("cd");
}

void    ft_pwd(void)
{
   char cwd[2000];

   if (getcwd(cwd, sizeof(cwd)) != NULL)
	   ft_putstr(cwd);
   else
	   perror("getcwd() error");
	ft_putstr("\n");
}
