#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


extern char **environ;


/**
 * struct runtimedata - structure of data on runtime
 * @argve: argument vector
 * @inp: user's written command line 
 * @args:  command line arguments
 * @status: previous shell status
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct runtimedata
{
	char **argve;
	char *inp;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shell_data;

/**
 * struct seperators - single linked list
 * @separator: includes ;, |, and &
 * @next: next node
 * Description:  store separators
 */
typedef struct seperators
{
	char separator;
	struct seperators *next;
} list_sep;

/**
 * struct command_command_lists - single linked list
 * @line: command line
 * @next: link to next node
 * Description: stores command lines
 */
typedef struct command_command_lists
{
	char *line;
	struct command_command_lists *next;
} command_list;

/**
 * struct variable_list - linked list
 * @var_len: variable length
 * @valu: variable valuue
 * @val_lenu: valuue length
 * @next: next node link
 * Description: stores variables
 */
typedef struct variable_list
{
	int var_len;
	char *valu;
	int val_lenu;
	struct variable_list *next;
} var;

/**
 * struct builtin - Builtin command arguments structure.
 * @name: builtin command name
 * @f: pointer function for data type .
 */
typedef struct builtin
{
	char *name;
	int (*f)(shell_data *datashell);
} builtin_t;

/* aux_lists.c */
list_sep *add_sep(list_sep **head, char sep);
void free_list_sep(list_sep **head);
command_list *add_line(command_list **head, char *line);
void free_command_list(command_list **head);

/* aux_lists2.c */
var *add_var(var **head, int lvar, char *var, int lvalu);
void free_var(var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3.c */
void rev_string(char *s);

/* error_check_syntax.c */
int char_repeated(char *input, int i);
int err_sep(char *input, int i, char last);
int first_char(char *input, int *i);
void err_print_syntax(shell_data *datashell, char *input, int i, int bool);
int error_check_syntax(shell_data *datashell, char *input);

/* terminal_loop.c */
char *uncommented(char *in);
void terminal_loop(shell_data *datashell);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(list_sep **head_s, command_list **head_l, char *input);
void go_next(list_sep **list_s, command_list **list_l, shell_data *datashell);
int split_commands(shell_data *datashell, char *input);
char **split_line(char *input);

/* rep_var.c */
void check_env(var **h, char *in, shell_data *data);
int check_vars(var **h, char *in, char *st, shell_data *data);
char *replaced_input(var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, shell_data *datashell);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(shell_data *datashell);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_data *datashell);
int check_error_cmd(char *dir, shell_data *datashell);
int cmd_exec(shell_data *datashell);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(shell_data *datashell);

/* env2.c */
char *copy_info(char *name, char *valuue);
void set_env(char *name, char *valuue, shell_data *datashell);
int _setenv(shell_data *datashell);
int _unsetenv(shell_data *datashell);

/* cd.c */
void cd_dot(shell_data *datashell);
void cd_to(shell_data *datashell);
void cd_previous(shell_data *datashell);
void cd_to_home(shell_data *datashell);

/* cd_shell.c */
int cd_shell(shell_data *datashell);

/* get_builtin */
int (*get_builtin(char *cmd))(shell_data *datashell);

/* _exit.c */
int exit_shell(shell_data *datashell);

/* aux_stdlib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1.c */
char *strcat_cd(shell_data *, char *, char *, char *);
char *error_get_cd(shell_data *datashell);
char *error_not_found(shell_data *datashell);
char *error_exit_shell(shell_data *datashell);

/* aux_error2.c */
char *error_get_alias(char **args);
char *error_env(shell_data *datashell);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(shell_data *datashell);


/* get_error.c */
int get_error(shell_data *datashell, int evalu);

/* get_sigint.c */
void get_sigint(int sig);

/* aux_help.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help.c */
int get_help(shell_data *datashell);

#endif
