/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/28 00:28:05 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// opendir( const char * dirname )
// cd ..
int cd_dir(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) 
 		return 0;
    return S_ISDIR(info.st_mode);
}
void cd_checker(t_command **command)
{
	t_command *exec;
	char *current_directory = NULL;
    static char *path;
	int i =0;
	
	exec = *command;
	current_directory = (char *)malloc(PATH_MAX);
    if (!current_directory)
        ft_exit_fail("current dir problem_cd");

	if (getcwd(current_directory, PATH_MAX) == NULL)
	{
		if (path)
		{
			// printf("static : %s  and cuurent %s\n", path, current_directory);
			i = ft_strlen(path);
			while(i > 0)
			{
				if (path[i] == '/')
					break ;
				i--;
			}
			if (path[i] == '/') 
                path[i] = '\0';
			if (cd_dir(path))
			{
				printf("path changed to %s\n", path);
				chdir(path);
			}
			
		}
		if(!cd_dir(path))
			perror("current dir problem_cd2");
		free(current_directory);
		return ;
	}
	if (cd_dir(exec->args[1]))
	{
		chdir(exec->args[1]);
		getcwd(current_directory, PATH_MAX);
		path = current_directory;
		printf("path changed to this %s\n", path);
	}
	else
	{
		if (exec->args[1] != NULL && ft_strncmp(exec->args[1], "~", 2)
		&& ft_strncmp(exec->args[1], "~/", 2))
		{
			current_directory = ft_strjoin(current_directory, "/");
			if (!current_directory)
			    ft_exit_fail("current_directory_cd");
			path = ft_strjoin(current_directory, exec->args[1]);
			if (!path)
			    ft_exit_fail("Path problem_cd");	
		}
		else if (exec->args[1] == NULL || (exec->args[1] != NULL &&
			!ft_strncmp(exec->args[1], "~", 2)))
			path = getenv("HOME"); 
		if (cd_dir(path))
		{
			printf("path changed to %s\n", path);
			chdir(path);
		}
		else
			printf("Is not a Directory -> path %s\n", path);
	}
	free(current_directory);
}


