#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<libc.h>


int main() {
    const char *filename = "a.out";

    // Check if the file "example.txt" exists and is readable
    if (access(filename, F_OK | R_OK | W_OK) == 0) {
        printf("%s exists and is readable\n", filename);
    } else {
        perror("Error");
    }

    return 0;
}

