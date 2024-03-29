#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <dirent.h>
# include "./libft/libft.h"

enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
};

enum e_token
{ 
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
};

typedef struct s_exec
{
	int index;
	int i;
	int j;
	char *name;
	char *value;
	char *path_in;
    char **path_split;
    char *current_dir;
    char *path;
    char *exec_path;

} t_exec;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	*redir_in;
	char	*redir_out;
	char	*here_doc;
	char	*dredir_out;
	char	*content;
	int		pipe;
	int		redir;
	struct s_command	*next;
}	t_command;

typedef struct s_elem
{
	char			    *content;
	int				    len;
	enum e_state	state;
    struct s_elem	*next;
	enum e_token	token;
	struct s_elem	*prev;
}	t_elem;

void		*lexer(char *line, t_elem **elem);
t_elem		*lstnew(void *content, int token , t_elem **prev);
t_elem		*lstlast(t_elem *lst);
void		lstadd_back(t_elem **lst, t_elem *new);
void		state(t_elem **elem);
void syntax_error(t_elem **elem , int *flag);
void	stack_command(t_elem *elem, t_command **command, char **env);
t_command	*lstnew_command(char **agrs, char *cmd);
void		lstadd_back_command(t_command **lst, t_command *new);
void	stack_env(t_elem **elem, char **env);
// hamza
void exec_check(t_command **command, char **env);
void exec_path(t_command **command, char **env);
void cd_checker(t_command **command);
void ft_exit_fail(char *str);
char *get_env_exec(t_command **command, char **env);
void	ft_free_double(char **str);
void	ft_exit_fail(char *str);
int command_check(t_command **command);
#endif