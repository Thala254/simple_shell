#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <limits.h>

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;

/**
 * struct mybuild - pointer to function with corresponding buildin command
 * @name: buildin command
 * @func: execute the buildin command
 */
typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;

extern char **environ;
int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
char *_strdup(char *str);
char *concat_strings(char *name, char *sep, char *value);
char **splitstring(char *str, const char *delim);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
void execute(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void freearv(char **arv);
void(*checkbuiltinfnc(char **arv))(char **arv);
int _atoi(char *s);
void exitshell(char **arv);
void print_env(char **arv);
void _setenv(char **arv);
void _unsetenv(char **arv);
char *_getenv(const char *name);
char *var_build(char *var_name, char *var_value);
list_path *add_node_end(list_path **head, char *str);
list_path *linkpath(char *path);
char *_which(char *filename, list_path *head);
char *get_cwd(void);
int cd_home(void);
int cd_prev(void);
void _cd(char **args);
int tok_len(char *str, char *delim);
int tok_count(char *str, char *delim);
char **_strtok(char *str, char *delim);
void line_ptr(char **lineptr, size_t *n, char *buf, size_t size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void line_part(char **line, ssize_t len);
ssize_t get_new_len(char *line);
void operator_check(char *line, ssize_t *new_line);

#endif
