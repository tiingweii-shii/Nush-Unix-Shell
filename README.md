## Nush Unix Shell
### Overview
Nush (Northeastern University Shell) is a custom Unix Shell designed to provide a command-line interface with support for executing external programs, bash built-in commands, and operators. It supports interactive mode and script file execution, making it a powerful tool for both manual and automated command execution.

This project was the first challenge assignment for [CS 3650 Computer Systems](https://searchneu.com/NEU/202110/search/CS3650) at Northeastern University.


### Features
- Command Execution:
    - Run external programs and built-in commands.
    - Support for operators and multi-process execution.
- Scripting Support:
    - Execute commands from script files for automation.
- Interactive Mode:
    - Engage with a user-friendly interactive prompt.
- Redirection and Pipes:
    - Input/output redirection (<, >, >>).
    - Pipe multiple commands together (|).
- Background Processes:
    - Execute commands in the background using the & operator.
- Error Handling:
    - Provide meaningful error messages for syntax and execution failures.
- Signals and Signal Handling:
    - Gracefully handle exit and signals like Ctrl+C.
- Job Control:
    - Basic job control features, including foreground and background processes.

## Usage
#### Interactive Mode
Run the shell in interactive mode:
```
$ ./nush
```
#### Script File Execution
Execute commands from a script file:
```
$ ./nush tests/01-echo-one.sh
```
#### Examples
- Run an external command:
    ```
    nush$ echo hello
    ```
- Execute a built-in command:
    ```
    nush$ cd /path/to/directory
    ```
    ```
    nush$ pwd
    ```
- Redirect input/output:
    ```
    nush$ head -n 2 < test.txt
    nush$ echo one > test.txt
    ```
- Run commands in the background:
    ```
    $ command1 & command2
    ```
- Pipeline Operator
    ```
    nush$ sort sample.txt | uniq
    ```
- And Operator
    ```
    nush$ true && echo true
    nush$ echo one && echo two
    ```
- Or Operator
    ```
    nush$ false || echo false
    nush$ echo one || echo two
    ```
- Semicolon Operator
    ```
    nush$ echo one; cat sample.txt
    ```
- Variables
    ```
    nush$ FOO=one
    nush$ BAR=two
    nush$ echo $FOO $BAR $FOO
    nush$ FOO=three
    nush$ echo $BAR $FOO $BAR
    ```
#### Installation
Clone the repository:
```
$ git clone https://github.com/tiingweii-shii/Nush-Unix-Shell
```
Compile the shell:
```
$ make
```
Run the shell:
```
$ ./nush
```
To exit the shell:
```
$ exit
```
