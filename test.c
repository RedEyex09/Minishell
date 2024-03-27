#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (chdir(argv[1]) == -1) {
        perror("chdir");
        return 1;
    }

    printf("Current directory changed to: %s\n", argv[1]);
    return 0;
}
