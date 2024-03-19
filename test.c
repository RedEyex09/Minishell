
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
    int fd;
    struct stat file_info;

    // Open a file
    fd = open("text.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Retrieve information about the open file
    if (fstat(fd, &file_info) == 0) {
        printf("File size: %lld bytes\n", file_info.st_size);
        printf("File mode: %o\n", file_info.st_mode);
        // Access other file attributes as needed
    } else {
        perror("fstat");
        return 1;
    }

    // Close the file
    close(fd);

    return 0;
}



