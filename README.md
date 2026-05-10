```md
*This project has been created as part of the 42 curriculum by doleksiu, alusnia.*

# Minishell

## Description

Minishell is a 42 School project focused on creating a simple Unix shell in C. 
The goal of the project is to understand how shells work internally, especially command parsing, process creation, file descriptors, pipes, redirections, environment variables, signals, and built-in commands.

This project recreates a small but functional shell inspired by `bash`. It displays an interactive prompt, reads user input, parses commands, expands variables, executes programs, and handles common shell behaviors.

The project was developed by:

- **doleksiu** — tokenizer, expander, parser, signals
- **alusnia** — executor, hash table

## Features

Minishell supports:

- Interactive prompt
- Command history
- Execution of commands using:
  - absolute paths
  - relative paths
  - `PATH` environment variable
- Single quotes `'...'`
- Double quotes `"..."`
- Environment variable expansion using `$VAR`
- Exit status expansion using `$?`
- Pipes using `|`
- Redirections:
  - `<` input redirection
  - `>` output redirection
  - `>>` append output redirection
  - `<<` heredoc
- Signal handling:
  - `Ctrl-C`
  - `Ctrl-D`
  - `Ctrl-\`
- Built-in commands:
  - `echo` with `-n`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Project Structure

The project is divided into several main parts:

### Tokenizer, Expander, Parser & Signals

Implemented by **doleksiu**.

- **Tokenizer:** Responsible solely for lexical analysis and splitting the raw input string into individual **tokens**.
- **Expander:** Handles variable expansions ($VAR, $?). It is also responsible for quote removal and passing the ordered and expanded tokens to the parser, ensuring correct context interpretation.
- **Parser:** Receives the prepared tokens and builds a structure ready for execution, handling redirection logic and command organization for the executor.
- **Signals:** Signal handling makes the shell behave similarly to `bash` in interactive mode:
  - `Ctrl-C` displays a new prompt on a new line
  - `Ctrl-D` exits the shell
  - `Ctrl-\` does nothing

### Executor & Hash Table

Implemented by **alusnia**.

- **Executor:** Responsible for running parsed commands. It handles built-in command execution, external commands with `execve`, process creation with `fork`, pipes, and file descriptor management.
- **Hash Table:** Implemented to efficiently store and manage environment variables, allowing for fast lookup, addition, and removal of variables.

## Instructions

### Compilation

To compile the project, run:

```sh
make

```

This will create the `minishell` executable.

### Running the shell

After compilation, start Minishell with:

```sh
./minishell

```

### Cleaning

To remove object files, run:

```sh
make clean

```

To remove object files and the executable, run:

```sh
make fclean

```

To rebuild the project from scratch, run:

```sh
make re

```

## Usage Examples

### Pipes and Redirections

```sh
minishell$ ls | grep mini > output.txt
minishell$ cat < output.txt

```

### Heredoc

```sh
minishell$ cat << EOF
hello
world
EOF

```

## Built-in Commands

| Command | Description |
| --- | --- |
| `echo` | Prints arguments to standard output, supports the `-n` option |
| `cd` | Changes the current working directory |
| `pwd` | Prints the current working directory |
| `export` | Adds or displays environment variables |
| `unset` | Removes environment variables |
| `env` | Displays the environment |
| `exit` | Exits the shell |

## Error Handling

Minishell handles common shell errors and execution failures. Allocated memory is freed when necessary. While `readline` may report internal leaks (as allowed by the subject), the project code aims to be free of memory leaks.

## Limitations

The project follows the 42 subject requirements:

* No unclosed quotes interpretation.
* No backslash or semicolon handling.
* No logical operators like `&&` or `||`.

## Resources

* Bash manual: https://www.gnu.org/software/bash/manual/bash.html
* GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
* Readline `rl_catch_signals`: https://www.manpagez.com/info/rlman/rlman-5.2/rlman_43.php
* GNU C Library (termios modes / local modes): https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
* Unix Processes in C YouTube Playlist (CodeVault): https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
* Linux manual pages for different functions used in the program.
* Various programming forums for troubleshooting and conceptual understanding.

### AI Usage

AI tools were used to help structure this documentation, improve clarity, and prepare usage examples. The final technical implementation and logic remain the responsibility of the authors.

```

```