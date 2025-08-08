# Minishell - Command Parsing and Process Management
[![42 School: Rank 3](https://img.shields.io/badge/42%20School-Rank%203-%2315bbbb)](https://www.42network.org/)

_Minishell is a project about creating a simple custom UNIX shell in C, focusing on process control, file descriptor management, and command parsing._

___


### Table of contents
[Features](#features) · [Usage](#usage) · [License](#license) · [Study Notes](#study-notes)

___

</br>

## Features

- Lexical analysis and tokenization of command-line input

- Parsing and syntax interpretation for complex command structures

- Process creation and management for command execution

- Environment state management with variable expansion

- Inter-process communication via pipes

- Input/output redirection and here-document handling

- Pattern matching for dynamic filename expansion (wildcards)

- Conditional and grouped command execution with logical operators

- Quote handling for argument grouping (single and double quotes)

- Signal handling for interactive session control

- Robust error handling and resource management

</br>

## Usage
### Setup and compilation

1. Clone repository
    ```bash
    git clone git@github.com:teresa-chow/42-minishell.git minishell
    ```

2. Go inside project directory and run `make`
    ```bash
    cd minishell
    make
    ```

3. Execute `minishell` program
    ```bash
    ./minishell
    ```

___

</br>

### License
This work is published under the terms of [MIT License](./LICENSE).

</br>

#### Study notes

Further reading : [Wiki](https://github.com/teresa-chow/42-minishell/wiki)

</br></br>

[⬆ back to top](#minishell---command-parsing-and-process-management)
