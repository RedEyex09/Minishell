
#include <readline/readline.h>
#include <readline/history.h>
#include<libc.h>
#include <errno.h>

#include <stdio.h>
#include <unistd.h>

int main() {
    const char *new_directory = "/Users/zaki";
    char cwd[1024]; // Assuming the path won't exceed 1024 characters
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd");
        return 1;
    }
    if (chdir(new_directory) == 0) {
        printf("Changed directory to: %s\n", new_directory);
    } else {
        perror("chdir");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    return 0;
}

