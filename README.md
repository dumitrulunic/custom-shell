# Run the Makefile
make

# Run the imcsh shell
./imcsh

# Technical Documentation
exec ls -l              # List files
exec sleep 5 &          # Run sleep in background
globalusage            # Show version
globalusage > version.txt # redirects output to file
exec ps > output.txt   # Redirect output to file
quit                   # Exit the shell

# After testing
make clean