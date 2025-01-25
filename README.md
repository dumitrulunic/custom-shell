# Run the Makefile
make

# Run the imcsh shell
./imcsh

# Commands
# exec <program_to_execute>:
exec ls -l
exec ps -uax
exec echo "Hello, World!"

# Modifier &:
exec sleep 3 &
exec ls -l &
exec echo "Running in background" &

# globalusage:
globalusage

# Modifier >:
exec ls -l > directory_output.txt
exec ps -uax > process_output.txt
globalusage > usage.txt

# quit:

quit (with no background processes running)
exec sleep 10 & followed by quit (with background processes running)

# After testing
make clean