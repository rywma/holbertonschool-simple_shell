# Simple Shell

A simple UNIX command line interpreter written in C

## Description

`hsh` is a simple shell that replicates the functionality of `/bin/sh`
It reads commands from standard input then finds programs using the `PATH`
variable, and executes them using `fork` and `execve`

## Authors

Noura Alosaimi & Reema Almujalli

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
