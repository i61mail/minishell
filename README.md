## Minishell

[![Build](https://img.shields.io/badge/build-make-brightgreen.svg)](https://github.com/i61mail/minishell)

A minimal Unix shell implemented in C. Minishell reproduces essential shell features: command execution, redirections, pipes, environment variable handling, built-in commands, quote processing and heredocs.

## Table of Contents

- [Features](#features)
- [Prerequisites & Build](#prerequisites--build)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Operators & Redirections](#operators--redirections)
- [Project Structure](#project-structure)
- [Implementation Details](#Implementation-Details)
- [Acknowledgments](#Acknowledgments)

## Features

## Core Shell Functionality

- Interactive prompt with readline support (command history, line editing)
- Command execution from PATH or absolute/relative paths
- Pipes (|) to chain multiple commands
- Redirections for input/output management
- Environment variable expansion with $ syntax
- Quote handling (single ' and double " quotes)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-'\')
- Here-documents with variable expansion control

## Prerequisites & Build

You will need:

- GCC (or compatible C compiler)
- GNU Make
- Readline library (libreadline-dev)

On Debian/Ubuntu:

```sh
sudo apt-get update && sudo apt-get install -y build-essential libreadline-dev
```

Build the project:

```sh
make
```

Common make targets:

- `make` — build the `minishell` executable
- `make clean` — remove object files
- `make fclean` — remove object files and executable
- `make re` — rebuild from scratch

## Usage

Run the shell from the repository root:

```sh
./minishell
```

You'll see a prompt like:

```
minishell> 
```

Examples:

```sh
minishell> ls -la
minishell> echo "Hello, World!"
minishell> cat file.txt | grep "pattern" | wc -l
minishell> exit
minishell> echo $USER "$USER" '$USER'
```

## Built-in Commands

- echo: print arguments to stdout
  - `echo -n` suppresses trailing newline
- cd: change the working directory
  - `cd -` returns to OLDPWD, `cd` with no args goes to HOME
- pwd: print working directory
- export: set or show environment variables
- unset: remove environment variables
- env: show environment variables
- exit: leave the shell (optionally with a numeric code)

## Operators & Redirections

- Pipes: `cmd1 | cmd2 | cmd3`
- Input redirection: `cmd < file`
- Output redirection (overwrite): `cmd > file`
- Append redirection: `cmd >> file`
- Here-doc (`<<`): read until a delimiter
  - Unquoted delimiter: variables expand
  - Quoted delimiter: variables are treated literally

## Project Structure

```
minishell/
├── Makefile
├── minishell.h
├── main.c
├── main2.c
├── execution/
│   ├── ft_execute.c
│   ├── ft_execute2.c
│   ├── builtins/
│   │   ├── ft_cd.c
│   │   ├── ft_echo.c
│   │   ├── ft_env.c
│   │   ├── ft_exit.c
│   │   ├── ft_export.c
│   │   ├── ft_pwd.c
│   │   └── ft_unset.c
│   └── utils/
│       ├── ft_exec_utils.c
│       ├── ft_exec_utils1.c
│       └── ft_red_utils.c
├── parsing/
│   ├── env.c
│   └── env_utils.c
└── utils/
    ├── alpha.c
    ├── dollar.c
    ├── expanding.c
    ├── quotes.c
    ├── separator.c
    ├── token.c
    └── heredoc/
        ├── heredoc.c
        ├── heredoc_delimiter.c
        └── heredoc_expansion.c
```

## Implementation Details


## Architecture

## Parsing Phase:

- Tokenization - Input is split into tokens (commands, operators, arguments)
- Quote Processing - Handle single/double quotes and escaping
- Variable Expansion - Expand $VAR and special variables
- Heredoc Processing - Handle << operators with temporary files
- Syntax Validation - Check for syntax errors

## Execution Phase:

- Pipeline Setup - Create pipes for command chaining
- Fork & Execute - Fork processes for external commands
- Built-in Handling - Execute built-ins in the parent process (single command) or child (pipes)
- Redirection Setup - Handle file descriptors for <, >, >>, <<
- Wait & Status - Collect exit statuses from child processes

## Acknowledgments

- This project it provides hands-on experience with:

- Process management (fork, exec, wait)
- File descriptor manipulation
- Signal handling
- Parsing and lexical analysis
- Memory management in C