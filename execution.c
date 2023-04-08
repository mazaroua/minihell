/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 15:38:01 by mazaroua          #+#    #+#             */
/*   Updated: 2023/04/08 17:54:41 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main_builtins(t_cmd_line **cmd_line)
{
    if ((*cmd_line) && (*cmd_line)->str[0])
    {
        if (!ft_strcmp((*cmd_line)->str[0], "cd"))
            return (1);
        else if (!ft_strcmp((*cmd_line)->str[0], "export") && (*cmd_line)->str[1])
            return (1);
        if (!ft_strcmp((*cmd_line)->str[0], "unset"))
            return (1);
        if (!ft_strcmp((*cmd_line)->str[0], "exit"))
            return (1);
    }
    return (0);
}

void    execute_builtins(t_cmd_line **cmd_line, t_env_list **env_list)
{
    if (!ft_strcmp((*cmd_line)->str[0], "cd"))
        ft_cd((*cmd_line)->str[1], env_list);
    // else if (!ft_strcmp((*cmd_line)->str[0], "export") && (*cmd_line)->str[1])
    //     ft_export();
    // else if (!ft_strcmp((*cmd_line)->str[0], "unset"))
    //     ft_unset();
    // else if (!ft_strcmp((*cmd_line)->str[0], "exit"))
    //     ft_exit();
}

int count_commands(t_cmd_line **cmd_line)
{
    t_cmd_line  *cmd;
    int         count;

    cmd = *cmd_line;
    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}


int	builtins(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (2);
	if (!ft_strcmp(cmd, "pwd"))
		return (3);
	if (!ft_strcmp(cmd, "env"))
		return (4);
	if (!ft_strcmp(cmd, "export"))
		return (5);
	if (!ft_strcmp(cmd, "unset"))
		return (6);
	if (!ft_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

void	exec_builtins(char	**str, t_env_list **env_list, int code)
{
	if (code == 1)
		echo_cmd();
	if (code == 2)
		ft_cd(str[1], env_list);
	if (code == 3)
		ft_pwd();
	if (code == 4)
		ft_env(str, env_list);
	if (code == 5)
		ft_export(str, env_list);
	if (code == 6)
		ft_unset(str, env_list);
	if (code == 7)
		ft_exit(str);
}

void	execute_command_2(t_cmd_line **cmd_line, t_env_list **env_list)
{
	int	built_code;

	built_code = builtins((*cmd_line)->str[0]);
	if (built_code)
	{
		exec_builtins((*cmd_line)->str, env_list, built_code);
	}
	else
		execve_func((*cmd_line)->str, env_list);
}
void    execute_command(t_cmd_line **cmd_line, t_env_list **env_list)
{
	t_cmd_line *cmd_tmp = *cmd_line;
	int	cmds = count_commands(cmd_line);
	int	flag = 1;
	int	fd[2];
	while (cmd_tmp)
	{
        if (cmd_tmp->separator == e_pipe)
			pipe(fd);
		if (fork() == 0)
		{
			if (flag == 1)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			else if (flag > 1 && flag < count)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			else if (flag == count)
			{
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
			}
			execute_command_2(cmd_line, env_list);
		}
		cmd_tmp = cmd_tmp->next;
		flag += 1;
	}
}

void    execution(t_cmd_line **cmd_line, t_env_list **env_list)
{
    if ((*cmd_line) && main_builtins(cmd_line) && (*cmd_line)->separator == e_nline)
        execute_builtins(cmd_line, env_list);
    else if ((*cmd_line))
    {
        execute_command(cmd_line, env_list);
    }
}