# Simple Shell

A simple UNIX command line interpreter written in C

## Description

`hsh` is a simple shell that replicates the functionality of `/bin/sh`
It reads commands from standard input then finds programs using the `PATH` environment variable, and executes them using `fork` and `execve`

## Usage

**Interactive Mode**

$ ./hsh
($) /bin./l
($) /bin/pwd
($) exit


**Noninteractive Mode**

$ echo "/bin/ls" | ./hsh
$ cat commands.txt|./hsh

## Features

- Searches commands using PATH enviroment variable
- Execute commands with/out arguments
- Works in interactive and non interactive modes
- Builtin commands: exit env
- Error messages match "/bin/sh" format

## Files

| File | Description |
| --- | --- |
| main.c | Entry point & main shell loop |
| execute.c | Forks child process then runs command |
| path.c | Searches PATH for commands |
| tokenize.c | Splits input to arguments |
| utils.c | Helper functions |
| shell.h | Header file |

## Examples

**Succuessful Example**

$ ./hsh
($) /bin/ls-la
($) /bin/echo hello world
($) env
($) exit

**Error Example**

$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Authors

Noura Alosaimi & Reema Almujalli
