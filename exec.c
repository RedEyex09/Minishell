#include "minishell.h"
void ft_exit_fail(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}
void exec_path(t_command **command)
{
    t_command *exec;
    char *path_in;
    char **path_split;
    char *path;
    char *exec_path;
    int i = 0;

    exec = *command;
    path_in = getenv("PATH");
    path_split = ft_split(path_in, ':');
    if(!path_split)
        ft_exit_fail("path_split problem");
    while(path_split[i])
    {
        path = ft_strjoin(path_split[i], "/");
        if(!path)
            ft_exit_fail("path problem");
        exec_path = ft_strjoin(path, exec->args[0]);
        if(!exec)
            ft_exit_fail("exec path problem");
        if(access(exec_path, X_OK) == 0)
        {
            free(path);
            break ;
        }
        else
        {
            free(path);
            free(exec_path);
            i++;
        }

    }
    i =0 ;
    while (exec->args[i])
    {
        printf("exec->args ->%s<- \n",exec->args[i]);
        i++;
    }
    printf("exec_path ->%s<-", exec_path);
    if (execve((const char *)exec_path, (char *const *)exec->args, NULL) == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
}


void exec_check(t_command **command)
{
    int state;
    pid_t pid;

    pid = fork();
    if (pid == 0) //child process
        exec_path(command);
     else if (pid > 0 ) 
     { // Parent process
        if (waitpid(0, &state, 0) == -1) 
            perror("waitpid");
    }
    else
        perror("fork");

}
