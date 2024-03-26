#include <libc.h>

    t_command *exec = *command;
    char *path_in = getenv("PATH");
    char **path_split = ft_split(path_in, ':');
    if (!path_split) {
        perror("path_split problem");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    char *path = NULL;
    while (path_split[i]) {
        path = ft_strjoin(path_split[i], "/");
        if (!path) {
            perror("path problem");
            exit(EXIT_FAILURE);
        }

        char *executable_path = ft_strjoin(path, exec->args[0]);
        if (!executable_path) {
            perror("path problem");
            exit(EXIT_FAILURE);
        }

        if (access(executable_path, X_OK) == 0) {
            printf("Executable found: %s\n", executable_path);
            break;
        }

        free(executable_path);
        free(path);
        i++;
    }

    if (!path_split[i]) {
        fprintf(stderr, "Executable not found in PATH\n");
        exit(EXIT_FAILURE);
    }

    if (execve(path, exec->args, NULL) == -1) {
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}