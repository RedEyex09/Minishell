
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
    int fd1, fd2;

    // Open a file
    fd1 = open("example.txt", O_CREAT | O_RDWR);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    // Duplicate the file descriptor to file descriptor number 10
    fd2 = dup2(fd1, 10);
    if (fd2 == -1) {
        perror("dup2");
        close(fd1);
        return 1;
    }

    printf("File descriptors: %d, %d\n", fd1, fd2);

    // Close the original file descriptor
    close(fd1);

    // Use the duplicated file descriptor (fd2)...

    // Close the duplicated file descriptor
    close(fd2);

    return 0;
}



