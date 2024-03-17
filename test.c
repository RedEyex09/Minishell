
#include <readline/readline.h>
#include <readline/history.h>
#include<libc.h>
#include <errno.h>


int main() {
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process: PID=%d\n", getpid());
        sleep(2); // Simulate some work
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        // Wait for the specific child process to terminate
        wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        printf("Child process %d terminated with status %d\n", wpid, status);
    }

    return 0;
}