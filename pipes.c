#include "minishell.h"
// int	size_of_list(t_cmd_line *data)
// {
// 	int	counter;
// 	t_cmd_line *head;

// 	counter = 0;
// 	head = data;
// 	while (head)
// 	{
// 		counter++;
// 		head = head->next;
// 	}
// 	return (counter);
// }
void    do_pipes(t_cmd_line *data, int len,char *env[])
{
    //    int i = 0;
    // int pid;
    // t_cmd_line *head = data;
    // int fd[len - 1][2];

    // // create pipes
    // while (i < len - 1) {
    //     if (pipe(fd[i]) == -1) {
    //         perror("pipe");
    //         exit(EXIT_FAILURE);
    //     }
    //     i++;
    // }

    // // execute commands in pipeline
    // i = 0;
    // while (head != NULL) {
    //     pid = fork();
    //     if (pid == -1) {
    //         perror("fork");
    //         exit(EXIT_FAILURE);
    //     } else if (pid == 0) { // child process
    //         if (i == 0) { // first child process
    //             dup2(fd[i][1], STDOUT_FILENO);
    //             close(fd[i][0]);
    //             close(fd[i][1]);
    //         } else if (i == len-1) { // last child process
    //             dup2(fd[i-1][0], STDIN_FILENO);
    //             close(fd[i-1][0]);
    //             close(fd[i-1][1]);
    //         } else { // middle child process
    //             dup2(fd[i-1][0], STDIN_FILENO);
    //             dup2(fd[i][1], STDOUT_FILENO);
    //             close(fd[i-1][0]);
    //             close(fd[i-1][1]);
    //             close(fd[i][0]);
    //             close(fd[i][1]);
    //         }
    //         excuter(head->str, env);
    //         exit(EXIT_FAILURE);
    //     }
    //     head = head->next;
    //     i++;
    // }

    // // close pipes
    // i = 0;
    // while (i < len - 1) {
    //     close(fd[i][0]);
    //     close(fd[i][1]);
    //     i++;
    // }

    // // wait for all child processes to complete
    // i = 0;
    // while (i < len) {
    //     wait(NULL);
    //     i++;
    // }

}