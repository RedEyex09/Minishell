
#include <readline/readline.h>
#include <readline/history.h>
#include<libc.h>
#include <errno.h>

#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Path to the executable program
    const char *program_path = "/bin/ls";
    
    // Arguments to pass to the program
    char *const argv[] = { "ls", "-l", NULL };
    
    // Environment variables
    char *const envp[] = { NULL };

    // Execute the program
    if (execve(program_path, argv, envp) == -1) {
        perror("execve");
        return 1;
    }

    // This code won't be reached if execve is successful
    printf("This message won't be printed because execve succeeded.\n");

    return 0;
}



