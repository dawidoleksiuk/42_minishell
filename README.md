*This project has been created as part of the 42 curriculum by doleksiu, alusnia.*

# Minishell

## Description

Minishell is a 42 School project focused on creating a simple Unix shell in C. 
The goal of the project is to understand how shells work internally, especially command parsing, process creation, file descriptors, pipes, redirections, environment variables, signals, and built-in commands.

This project recreates a small but functional shell inspired by `bash`. It displays an interactive prompt, reads user input, parses commands, expands variables, executes programs, and handles common shell behaviors.

The project was developed by:

- **doleksiu** — tokenizer, expander, parser, signals
- **alusnia** — executor, hash table, built-in commands

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
- Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`) powered by an **encapsulated hash table** for highly efficient environment variable management.

## Project Structure

The project is divided into several main parts:

### Tokenizer, Expander, Parser & Signals

Implemented by **doleksiu**.

- **Tokenizer:** Responsible solely for lexical analysis and splitting the raw input string into individual **tokens**.
- **Expander:** Handles variable expansions (`$VAR`, `$?`). It is also responsible for quote removal and passing the ordered and expanded tokens to the parser, ensuring correct context interpretation.
- **Parser:** Receives the prepared tokens and builds a structure ready for execution, handling redirection logic and command organization for the executor.
- **Signals:** Signal handling makes the shell behave similarly to `bash` in interactive mode:
  - `Ctrl-C` displays a new prompt on a new line
  - `Ctrl-D` exits the shell
  - `Ctrl-\` does nothing

### Executor, Built-ins & Encapsulated Hash Table

Implemented by **alusnia**.

- **Executor & Built-ins:** Responsible for running parsed commands and implementing the core logic for all built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`). It also handles external commands with `execve`, process creation with `fork`, pipes, and file descriptor management.
- **Encapsulated Hash Table:** A custom data structure implemented to efficiently store and manage environment variables. By encapsulating the internal logic, it exposes a clean set of methods (for insertion, retrieval, and deletion) that directly power the `export`, `unset`, and `env` built-in commands. This ensures fast lookups and keeps the environment state management modular, isolated, and secure.

## Prerequisites

To compile and run this project, you need the following tools and libraries installed on your system:

- **C Compiler:** `gcc` or `clang`
- **Make:** To execute the build instructions
- **Git:** To fetch the required custom utility libraries during compilation
- **Readline Library:** Essential for the interactive prompt and command history

**For Ubuntu / Debian:**
```sh
sudo apt update
sudo apt install build-essential git libreadline-dev
```

**For macOS (using Homebrew):**
```sh
xcode-select --install
brew install readline
```

## Instructions

### Compilation

To compile the project, run:

```sh
make
```

> **Note on the Makefile:** This project uses a recursive Makefile. During the build process, it will automatically connect to GitHub to fetch the latest versions of our custom utility libraries (`libft`, `get_next_line`, `ft_printf`). Please do not be alarmed by the download process—this is intended behavior to ensure the shell is built with the most up-to-date and thoroughly tested foundational functions.

This will create the `minishell` executable.

### Running the shell

After compilation, start Minishell with:

```sh
./minishell
```

### Cleaning & Rebuilding

To remove locally generated object files, run:

```sh
make clean
```

To remove object files and the `minishell` executable, run:

```sh
make fclean
```

To perform a completely fresh build, run:

```sh
make re
```
> **Note on `make re`:** This command is designed to be thorough. It will completely remove the previously downloaded custom libraries (`libft`, `gnl`, `printf`) and fetch fresh, updated copies from GitHub before recompiling the entire project.

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
| `export` | Adds or modifies environment variables in the hash table |
| `unset` | Removes environment variables from the hash table |
| `env` | Displays all current environment variables |
| `exit` | Exits the shell safely |

## Error Handling

Minishell handles common shell errors and execution failures. Allocated memory is safely freed to ensure the project is free of memory leaks. Note: `readline` may report internal leaks, which are generally ignored per the 42 subject guidelines, but our own code strictly manages memory.

## Limitations

The project follows the 42 subject requirements:

* No unclosed quotes interpretation.
* No backslash or semicolon handling.
* No logical operators like `&&` or `||`.

## Resources

* Bash manual: https://www.gnu.org/software/bash/manual/bash.html
* Unix Processes in C YouTube Playlist (CodeVault): https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY
* GNU Readline documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
* Readline `rl_catch_signals`: https://www.manpagez.com/info/rlman/rlman-5.2/rlman_43.php
* GNU C Library (termios modes / local modes): https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_355.html
* Tokenizer https://mvsrgc.xyz/posts/Write-a-Shell-Tokenizer-in-C/
* Linux manual pages for different functions used in the program.
* Various programming forums for troubleshooting and conceptual understanding.

### AI Usage

During the development of this project, AI (Google Gemini) was utilized as an educational resource to clarify system-level concepts and streamline the debugging process. All insights were critically evaluated before application.

Specifically, AI assisted us with:

- **Understanding System Concepts:** Clarifying the underlying mechanics of OS-level functions, such as process duplication (`fork()`), inter-process communication (pipes), and terminal signal handling (`isatty`, `tcgetattr`, `sigaction`).
- **Debugging & Log Analysis:** Interpreting Valgrind memory leak reports, managing `readline` suppressions, and analyzing tester logs to resolve edge cases in variable expansion (e.g., `$VAR` and `$?`).
- **Architectural Brainstorming:** Discussing logical approaches for structuring the program and managing parent-child process states. We strictly avoided generating or copy-pasting C code, ensuring that the final implementation is entirely our own and fully understood.
- **Documentation:** Generating an initial structural draft of this README file, which was subsequently reviewed, refined, and validated against the project requirements.