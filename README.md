# 0x16. C - Simple Shell project

This is a simple UNIX command interpreter based on bash.

### Invocation

Usage: **shell**
To begin, all .c files should be compiled using the command:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o shell
./shell
```

**shell** can be invoked interactively and non-interactively. It reads and executes received commands in order If invoked with standard input not connected to a terminal.

Example:

```
$ echo "echo 'man'" | ./shell
'man'
$
```

If a command line argument is invoked, **shell** takes the first argument as a file from which to read commands.

Example:

```
$ cat txt
echo 'man'
$ ./shell txt
'man'
$
```

### Environment

Upon invocation, **shell** receives and copies the environment of the parent process in which it was executed. Some of the known environmental variables are:

#### HOME

Current user's home directory and the default directory argument for the **cd** builtin command.

```
$ echo "echo $HOME" | ./shell
/home/yobra
```

#### PWD

Current working directory set by the **cd** command.

```
$ echo "echo $PWD" | ./shell
/home/yobra/man
```

#### OLDPWD

Previous working directory set by the **cd** command.

```
$ echo "echo $OLDPWD" | ./shell
/home/yobra/menu
```

#### PATH

A colon-separated list of directories in which the shell looks for commands. A null directory name in the path indicates the current directory.

```
$ echo "echo $PATH" | ./shell
/home/yobra/.cargo/bin:/home/yobra/.local/bin:/home/yobra/.rbenv/plugins/ruby-build/bin:/home/yobra/.rbenv/shims:/home/yobra/.rbenv/bin:/home/yobra/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/yobra/.cargo/bin:/home/yobra/workflow:/home/yobra/.local/bin
```

### Command Execution

**shell** tokenizes the received commands into words using space as a delimiter. The first word is the command and all remaining words are arguments to that command.

### Exit Status

**shell** returns the exit status of the previous command executed. Zero indicates success and non-zero indicates failure.

### Signals

**shell** ignores ctrl+c keyboard input in interactive mode but an End-Of-File input i.e ctrl+d exits the program.

### Operators

#### ; - Command separator

Faciltates sequential execution of commands separated by ;

#### && - AND logical operator

Facilitates execution of both commands if exit status of the first command is zero.

#### || - OR logical operator

Faciltates execution of one of the two commnds whose exit status is zero.

## Authors & Copyrights

- Brian Kiprotich <[Thala254](https://github.com/Thala254)>
- Mercy Mukiri <[MercyMukiri](https://github.com/MercyMukiri)>

## More information

**Shell** is a simple shell unix commandline interpreter that emulates simple functionalities of the **sh** shell.
