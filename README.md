## Minishell

[![Build](https://img.shields.io/badge/build-make-brightgreen.svg)](https://github.com/i61mail/minishell)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A minimal Unix shell implemented in C for the 42 school curriculum. Minishell reproduces essential shell features: command execution, redirections, pipes, environment variable handling, built-in commands, quote processing and heredocs.

## Table of Contents

- [Features](#features)
- [Prerequisites & Build](#prerequisites--build)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Operators & Redirections](#operators--redirections)
- [Project Structure](#project-structure)
- [Development Notes](#development-notes)
- [Authors](#authors)
- [License](#license)

## Features

- Interactive prompt with line editing and history (readline)
- Execute binaries from PATH or by absolute/relative path
- Pipes (|) and multiple chained commands
- Input/output redirection (<, >, >>)
- Here-documents (<<) with optional variable expansion
- Environment variable expansion ($VAR) and special variables ($?, $$, $_)
- Proper handling of single and double quotes
- Built-in commands: cd, echo, pwd, export, unset, env, exit
- Signal handling for interactive use (Ctrl-C, Ctrl-D, Ctrl-\)

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

## Development Notes

- Parsing pipeline: tokenization → quote handling → expansion → syntax check
- Execution: build pipelines, fork/exec external commands, handle built-ins appropriately
- Built-ins may be executed in the parent (when not in a pipeline) or in child processes when in a pipeline
- Properly close file descriptors and free allocated memory to avoid leaks

Edge cases to keep in mind:

- Empty input or only whitespace
- Unclosed quotes or invalid operator sequences
- Ambiguous redirect targets
- Signals arriving during blocking syscalls

## Authors

- isrkik — 42 profile
- mait-lah — 42 profile

## License

This repository is provided for educational purposes. Add or confirm a LICENSE file if required.

---

If you'd like, I can also add a small example session GIF (or ASCII transcript), CI badge, or a CONTRIBUTING.md — tell me which and I'll add it next.
Minishell
A minimal Unix shell implementation written in C as part of the 42 school curriculum. This project recreates the basic functionality of bash, handling command execution, redirections, pipes, environment variables, and built-in commands.
Table of Contents

Features
Installation
Usage
Built-in Commands
Operators and Redirections
Environment Variables
Exit Status
Project Structure
Implementation Details

Features
Core Shell Functionality

Interactive prompt with readline support (command history, line editing)
Command execution from PATH or absolute/relative paths
Pipes (|) to chain multiple commands
Redirections for input/output management
Environment variable expansion with $ syntax
Quote handling (single ' and double " quotes)
Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
Here-documents with variable expansion control

Built-in Commands

echo with -n flag
cd with relative/absolute paths
pwd (print working directory)
export for environment variables
unset to remove environment variables
env to display environment
exit with numeric exit codes

Advanced Features

Multiple pipes support
Heredoc expansion based on delimiter quoting
Shell level tracking (SHLVL)
Ambiguous redirect detection
Comprehensive error handling

Installation
Prerequisites

GCC compiler
GNU Make
Readline library

On macOS (using Homebrew):
bashbrew install readline
On Linux (Ubuntu/Debian):
bashsudo apt-get install libreadline-dev
Build
bashmake
This will compile the project and create the minishell executable.
Clean
bashmake clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Rebuild from scratch
Usage
Starting the Shell
bash./minishell
```

You'll see the prompt:
```
minishell>
Basic Commands
bashminishell> ls -la
minishell> echo "Hello, World!"
minishell> cat file.txt | grep "pattern" | wc -l
Exit
bashminishell> exit
# or press Ctrl-D
Built-in Commands
echo
Prints arguments to standard output.
bashminishell> echo Hello World
Hello World

minishell> echo -n No newline
No newline minishell>

minishell> echo -nnn Multiple n flags
Multiple n flags minishell>
cd
Changes the current directory.
bashminishell> cd /path/to/directory
minishell> cd ..           # Go to parent directory
minishell> cd              # Go to HOME directory
minishell> cd -            # Go to previous directory (OLDPWD)
minishell> cd ~            # Go to HOME directory
pwd
Prints the current working directory.
bashminishell> pwd
/Users/username/project
export
Sets or displays environment variables.
bashminishell> export VAR=value
minishell> export VAR+=append
minishell> export            # Display all exported variables
unset
Removes environment variables.
bashminishell> unset VAR
minishell> unset VAR1 VAR2   # Remove multiple variables
env
Displays all environment variables.
bashminishell> env
exit
Exits the shell with an optional exit code.
bashminishell> exit              # Exit with last command's status
minishell> exit 42           # Exit with code 42
minishell> exit 256          # Code wraps: 256 % 256 = 0
Operators and Redirections
Pipes
Chain commands together:
bashminishell> ls -l | grep ".c" | wc -l
minishell> cat file.txt | tr 'a-z' 'A-Z' | sort
Input Redirection (<)
Read input from a file:
bashminishell> cat < input.txt
minishell> wc -l < file.txt
Output Redirection (>)
Write output to a file (overwrite):
bashminishell> echo "Hello" > output.txt
minishell> ls -la > files.txt
Append Redirection (>>)
Append output to a file:
bashminishell> echo "Line 1" >> output.txt
minishell> echo "Line 2" >> output.txt
Here-document (<<)
Read input until a delimiter is encountered:
bashminishell> cat << EOF
> This is line 1
> This is line 2
> EOF
Variable expansion in heredoc:

Unquoted delimiter: variables expand

bash  minishell> cat << EOF
  > $USER
  > EOF
  # Outputs the username

Quoted delimiter: no expansion

bash  minishell> cat << 'EOF'
  > $USER
  > EOF
  # Outputs: $USER
Environment Variables
Variable Expansion
bashminishell> echo $HOME
/Users/username

minishell> echo $PATH
/usr/local/bin:/usr/bin:/bin

minishell> echo $?           # Exit status of last command
0

minishell> echo $$           # Expands to literal $$
$$
Special Variables

$? - Exit status of the last command
$_ - Last argument of the previous command
$SHLVL - Current shell level (incremented with each nested shell)

Expansion Rules

Variables expand inside double quotes: "$VAR"
Variables don't expand inside single quotes: '$VAR'
Multiple $ signs: odd numbers expand one $, even numbers become literal

bashminishell> echo "$USER"      # Expands
minishell> echo '$USER'      # Doesn't expand: $USER
minishell> echo $$USER       # Expands to: $username
minishell> echo $$$USER      # Expands to: $username
Exit Status
The shell tracks the exit status of executed commands:

0 - Success
1 - General errors
126 - Permission denied
127 - Command not found
130 - Terminated by Ctrl-C (SIGINT)
131 - Terminated by Ctrl-\ (SIGQUIT)
255 - Invalid exit argument

Access the last exit status with $?:
bashminishell> ls /nonexistent
ls: /nonexistent: No such file or directory
minishell> echo $?
1
```

## Project Structure
```
minishell/
├── Makefile
├── minishell.h              # Main header file
## Minishell

[![Build](https://img.shields.io/badge/build-make-brightgreen.svg)](https://github.com/i61mail/minishell)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

A minimal Unix shell implemented in C for the 42 school curriculum. Minishell reproduces essential shell features: command execution, redirections, pipes, environment variable handling, built-in commands, quote processing and heredocs.

## Table of Contents

- [Features](#features)
- [Prerequisites & Build](#prerequisites--build)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Operators & Redirections](#operators--redirections)
- [Project Structure](#project-structure)
- [Development Notes](#development-notes)
- [Authors](#authors)
- [License](#license)

## Features

- Interactive prompt with line editing and history (readline)
- Execute binaries from PATH or by absolute/relative path
- Pipes (|) and multiple chained commands
- Input/output redirection (<, >, >>)
- Here-documents (<<) with optional variable expansion
- Environment variable expansion ($VAR) and special variables ($?, $$, $_)
- Proper handling of single and double quotes
- Built-in commands: cd, echo, pwd, export, unset, env, exit
- Signal handling for interactive use (Ctrl-C, Ctrl-D, Ctrl-\)

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
   ├── ft_execute2.c
   ├── builtins/
   │   ├── ft_cd.c
   │   ├── ft_echo.c
   │   ├── ft_env.c
   │   ├── ft_exit.c
   │   ├── ft_export.c
   │   ├── ft_pwd.c
   │   └── ft_unset.c
   └── utils/
       ├── ft_exec_utils.c
       ├── ft_exec_utils1.c
       └── ft_red_utils.c
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

## Development Notes

- Parsing pipeline: tokenization → quote handling → expansion → syntax check
- Execution: build pipelines, fork/exec external commands, handle built-ins appropriately
- Built-ins may be executed in the parent (when not in a pipeline) or in child processes when in a pipeline
- Properly close file descriptors and free allocated memory to avoid leaks

Edge cases to keep in mind:

- Empty input or only whitespace
- Unclosed quotes or invalid operator sequences
- Ambiguous redirect targets
- Signals arriving during blocking syscalls

## Authors

- isrkik — 42 profile
- mait-lah — 42 profile

## License

This repository is provided for educational purposes. Add or confirm a LICENSE file if required.

---

If you'd like, I can also add a small example session GIF (or ASCII transcript), CI badge, or a CONTRIBUTING.md — tell me which and I'll add it next.
