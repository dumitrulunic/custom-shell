# Technical documentation for IMCSH shell
#### Authors: Andrei-Flavius Văcaru & Lunic Dumitru

# Run the Makefile
```bash
make
```

> If you encounter an error, run the following command
```bash
make clean
```

# Run the IMCsh shell
```bash
./imcsh
```

# Commands

## exec <program_to_execute>:

```exec``` is a command to execute a program. The program can be any executable file in the system. 

```bash
exec ls -l
exec ps -uax
exec echo "Hello, World!"
```

### Modifier &:

Modifier ```&``` is used to run the command in the background. The shell will not wait for the command to finish before accepting the next command.

```bash
exec sleep 3 &
exec ls -l &
exec echo "Running in background" &
```

## globalusage command:

```globalusage``` is a command to print current version of IMCsh shell and the authors names.

```bash
globalusage
```

### Modifier >:

Modifier ```>``` is used to redirect the output of the command to a file.

```bash
exec ls -l > directory_output.txt
exec ps -uax > process_output.txt
globalusage > usage.txt
```

## quit:


```quit``` is a command to exit the shell, can be used to exit the shell at any time with or without background processes running. If using ```quit``` with background processes running, the shell will ask to confirm premature termination of the background processes.

```bash
quit 
```

> Full list of unix commands can be found [here](https://docs.rockylinux.org/books/admin_guide/03-commands/)