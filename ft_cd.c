/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-magh <hel-magh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:27:36 by hel-magh          #+#    #+#             */
/*   Updated: 2024/03/27 14:45:06 by hel-magh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// opendir( const char * dirname )
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
    char *path = NULL;
	
	exec = *command;
	current_directory = (char *)malloc(PATH_MAX);
    if (!current_directory || getcwd(current_directory, PATH_MAX) == NULL)
        ft_exit_fail("current dir problem_cd");
	current_directory = ft_strjoin(current_directory, "/");
    if (!current_directory)
        ft_exit_fail("current_directory_cd");
	path = ft_strjoin(current_directory, exec->args[1]);
    if (!path)
        ft_exit_fail("Path problem_cd");
	if (cd_dir(path))
	{
		printf("path changed\n");
		chdir(path);
	}
	else
		printf("Is not a Directory\n");
	
}
