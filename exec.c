/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:45 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/27 14:03:24 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *get_env_exec(t_command **command, char **env)
{
	int index = 0;
	int j = 0;

	char *env_name = malloc(sizeof(char) * 100);
	char *env_value = malloc(sizeof(char) * 100);
	env_name = ft_strdup((*command)->content);
	env_value = NULL;
	while (env[index])
	{
		if (ft_strncmp(env[index], env_name, ft_strlen(env_name)) == 0 && env[index][ft_strlen(env_name)] == '=')
		{
			while (env[index][j] != '=')
				j++;
			env_value = ft_strdup(env[index] + j + 1);
			break;
		}
		index++;
	}
	return (env_value);
}
void	ft_free_double(char **str)
{
	int	i;

	i = 0;
    if(str == NULL)
        return ;
	while (str[i])
	{
		free(str[i]);
        str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
void ft_exit_fail(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}
void exec_path(t_command **command, char **env) {
    t_command *exec;
    char *path_in;
    char **path_split;
    char *current_directory = NULL;
    char *path = NULL;
    char *exec_path = NULL;
    int i = 0;

    exec = *command;
    (*command)->content = "PATH";
    path_in = get_env_exec(command, env);
    current_directory = (char *)malloc(PATH_MAX);
    if (!current_directory || getcwd(current_directory, PATH_MAX) == NULL)
        ft_exit_fail("current dir problem");
    path = ft_strjoin(path_in, ":");
    if (!path)
        ft_exit_fail("Path problem");
    path = ft_strjoin(path, current_directory);
    if (!path)
        ft_exit_fail("Path problem");
    path_split = ft_split(path, ':');
    if (!path_split)
        ft_exit_fail("Path_split problem");
    while(path_split[i])
    {
        path = ft_strjoin(path_split[i], "/");
        if(!path)
            ft_exit_fail("path problem");
        exec_path = ft_strjoin(path, exec->args[0]);
        if(!exec_path)
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
    free(current_directory);
    ft_free_double(path_split);
    if (execve((const char *)exec_path, (char *const *)exec->args, env) == -1)
    {
        printf("Error: %s: command not found\n", exec->args[0]);
        exit(EXIT_FAILURE);
    }
}

int command_check(t_command **command)
{
    t_command *exec;

    exec = *command;
    if (!ft_strncmp("cd", exec->args[0], 3)
		||!ft_strncmp("CD", exec->args[0], 3))
        return (cd_checker(command), 0);
    else if (!ft_strncmp("echo", exec->args[0], 5)
			|| !ft_strncmp("ECHO", exec->args[0], 5))
        return (printf("it's echo\n"), 0);
    else if (!ft_strncmp("export", exec->args[0], 7)
			|| !ft_strncmp("EXPORT", exec->args[0], 7))
        return (printf("it's export\n"), 0);
    else if (!ft_strncmp("pwd", exec->args[0], 4)
			|| !ft_strncmp("PWD", exec->args[0], 4))
        return (printf("it's pwd\n"), 0);
    else if (!ft_strncmp("unset", exec->args[0], 6)
			|| !ft_strncmp("UNSET", exec->args[0], 6))
        return (printf("it's unset\n"), 0);
    else if (!ft_strncmp("env", exec->args[0], 4)
			|| !ft_strncmp("ENV", exec->args[0], 4))
        return (printf("it's env\n"), 0);
    else if (!ft_strncmp("exit", exec->args[0], 5)
			|| !ft_strncmp("EXIT", exec->args[0], 5))
        return (printf("it's exit\n"), 0);
    return(1);
}


void exec_check(t_command **command, char **env)
{
    int state;
    pid_t pid;

    if(command_check(command) == 1)
    {

            pid = fork();
            if (pid == 0) //child process
                exec_path(command, env);
             else if (pid > 0 ) 
             { // Parent process
                if (waitpid(0, &state, 0) == -1) 
                    perror("waitpid");
            }
            else
                perror("fork");
    }
    else
        return ;

}
