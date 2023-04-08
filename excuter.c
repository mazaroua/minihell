#include "minishell.h"
char	*check_path(char *paths[], char *commands[])
{
	int		i;
	char	*var1;
	char	*ful;

	i = 0;
	while (paths[i])
	{
		var1 = ft_strjoin("/", commands[0]);
		ful = ft_strjoin(paths[i++], var1);
		i++;
		if (access(ful, F_OK) == 0)
			return (ful);
		free(ful);
		free(var1);
	}
	return (NULL);
}
void	my_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
char	*get_path(char *env[])
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}
void	excuter(char **commands, char *env[])
{
	char	*ful;
	char	**paths;

	if (commands[0][0] == '/')
	{     
		if (access(commands[0], F_OK) == 0)
			ful = commands[0];
	}
	else
	{
		paths = ft_split(get_path(env), ':');
		if (!commands || !paths)
			my_error("error when check commands or paths");
		ful = check_path(paths, commands);
	}
	if (ful)
	{
		if (execve(ful, commands, env) == -1)
			my_error("error execve");
	}
	my_error("command not found");
}

void    first_cmd(t_cmd_line *data, char *env[])
{
    t_cmd_line *head= data;
	int fd;

	
    while (head->redirections)
    {
		
        	if (head->redirections->type == 3)
            {
                head->redirections->fd = open(head->redirections->file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
                dup2( head->redirections->fd,STDOUT_FILENO);
            }
            else if(head->redirections->type == 4)
            {
                    head->redirections->fd = open(head->redirections->file, O_RDONLY , 0777);
                    dup2(head->redirections->fd,STDIN_FILENO);
            }
            else if(head->redirections->type == 1)
            {
                head->redirections->fd = open(head->redirections->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
                dup2( head->redirections->fd,STDOUT_FILENO);
            }
        head->redirections = head->redirections->next;
    }
	excuter(head->str,env);
}

void    excute_one_cmd(t_cmd_line *data, char *env[])
{
    int pid;

	if (data->str == NULL)
	{
		return ;
	}
        pid = fork();
        if (pid == -1)
            my_error("error");
        if (pid == 0)
            first_cmd(data, env);
        wait(NULL);
}
