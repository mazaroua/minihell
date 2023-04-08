#include "minishell.h"

void do_cd(char *path)
{
    int i;

    if (path == NULL || path[0] == '~')
    {
        char *home_dir = getenv("HOME");
        if (home_dir == NULL)
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
