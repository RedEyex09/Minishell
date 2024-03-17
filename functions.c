        #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <termcap.h>

// readline - Reads a line from the input stream
char *readline(const char *prompt);

// readline - Clears the history list maintained by the readline library
void rl_clear_history(void);

// readline - Signals readline that a new line has been started
void rl_on_new_line(void);

// readline - Replaces the current line in the readline buffer with a new one
void rl_replace_line(const char *text, int clear_undo);

// readline - Refreshes the display after a change in the readline buffer
void rl_redisplay(void);

// readline - Adds a line to the history list
void add_history(const char *string);

// stdio.h - Prints formatted output to stdout
int printf(const char *format, ...);

// stdlib.h - Allocates memory on the heap
void *malloc(size_t size);
// stdlib.h - Frees memory previously allocated by malloc
void free(void *ptr);

// unistd.h - Writes data to a file descriptor
ssize_t write(int fd, const void *buf, size_t count);
// unistd.h - Checks the accessibility of a file
int access(const char *pathname, int mode);
// fcntl.h - Opens a file or creates a new one
int open(const char *pathname, int flags, mode_t mode);

// unistd.h - Reads data from a file descriptor
ssize_t read(int fd, void *buf, size_t count);
// unistd.h - Closes a file descriptor
int close(int fd);

// unistd.h - Creates a new process by duplicating the calling process
pid_t fork(void);
// sys/wait.h - Wait for child process to terminate
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

// signal.h - Signal handling functions
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int kill(pid_t pid, int sig);
// stdlib.h - Terminates the calling process
void exit(int status);

// unistd.h - Gets the current working directory
char *getcwd(char *buf, size_t size);
// unistd.h - Changes the current working directory
int chdir(const char *path);

// sys/stat.h - Get file status
int stat(const char *pathname, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);

// unistd.h - Deletes a name from the filesystem
int unlink(const char *pathname);

// unistd.h - Executes a program
int execve(const char *pathname, char *const argv[], char *const envp[]);
// unistd.h - Duplicates file descriptors
int dup(int oldfd);
int dup2(int oldfd, int newfd);
// unistd.h - Creates an interprocess communication pipe
int pipe(int pipefd[2]);

// dirent.h - Directory manipulation functions
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

// string.h - Returns a string describing an error code
char *strerror(int errnum);
// stdio.h - Prints a descriptive error message to stderr
void perror(const char *s);

// unistd.h - Checks if a file descriptor refers to a terminal
int isatty(int fd);
// unistd.h - Returns the name of the terminal associated with a file descriptor
char *ttyname(int fd);
// unistd.h - Gets the number of available terminal slots
int ttyslot(void);
// unistd.h - Performs device control operations
int ioctl(int fd, unsigned long request, ...);

// stdlib.h - Gets the value of an environment variable
char *getenv(const char *name);

// termios.h - Sets or gets terminal attributes
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
int tcgetattr(int fd, struct termios *termios_p);

// termcap.h - Terminal-related functions for termcap/terminfo database access
int tgetent(char *bp, const char *name);
int tgetflag(const char *id);
int tgetnum(const char *id);
char *tgetstr(const char *id, char **area);
char *tgoto(const char *cm, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
