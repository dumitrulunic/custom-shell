# Technical documentation for IMCSH shell

### Authors:
- [Andrei-Flavius Văcaru](https://github.com/VakaruGIT)
- [Dumitru Lunic](https://github.com/dumitrulunic)

### Built-in commands:
The shell has the capability to support built-in commands like "globalusage" and "quit" in order to exit the shell. These are handled internally by the shell

### External commands:
The shell has the capability to execute the external commands "exec" followed by the command to be executed. It also support modifiers like "&" which runs the command in background and ">" to redirect its output to one file. 

### Code organization
- In the `executor.c` file, we defined functions that execute commands (built-in and external).
- In the `main.c` file, we have an entry point for the shell (Running a loop until we quit the shell).
- In the `parser.c` file, we defined functions that parse the input from an user into commands.
- In the `shell.h` file, contains the function that runs the loop and handling of processes.
- Files like `Makefile`, `shell.h`, `executor.h`, `parser.h` are used for building the project and documentation.

### Testing the shell
In order to test each command please follow the next steps:
#### EXTRA REQUIREMENTS
- a gcc compiler
- a linux distribution

## 1. Run the Makefile
```bash
make
```
> If you encounter an error, run the following command
```bash
make clean
```

## 2. Run the IMCsh shell
```bash
./imcsh
```

## 3. exec <program_to_execute>:

```exec``` is a command to execute a program. The program can be any executable file in the system. 

```bash
exec ls -l
exec ps -uax
exec echo "Hello, World!"
```

### 4. Modifier &:

Modifier ```&``` is used to run the command in the background. The shell will not wait for the command to finish before accepting the next command.

```bash
exec sleep 3 &
exec ls -l &
exec echo "Running in background" &
```

### 5. globalusage command:

```globalusage``` is a command to print current version of IMCsh shell and the authors names.

```bash
globalusage
```

### 6. Modifier >:

Modifier ```>``` is used to redirect the output of the command to a file.

```bash
exec ls -l > directory_output.txt
exec ps -uax > process_output.txt
globalusage > usage.txt
```

### 8. quit:


```quit``` is a command to exit the shell, can be used to exit the shell at any time with or without background processes running. If using ```quit``` with background processes running, the shell will ask to confirm premature termination of the background processes.

```bash
quit 
```

### 9. Clean the project

```bash
make clean
```

> Full list of unix commands can be found [here](https://docs.rockylinux.org/books/admin_guide/03-commands/)

I hope you enjoyed the shell and found the documentation useful. If there any questions or suggestions, please let us know.
