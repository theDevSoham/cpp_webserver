#!/bin/bash

# Check if the user provided a file argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <cpp_file> [g++ flags...]"
    exit 1
fi

cpp_file="$1"
executable="${cpp_file%.cpp}"  # Remove the .cpp extension to get the executable name
shift  # Remove the first argument (cpp_file) from the arguments list

# Compile the C++ source file using g++ with additional flags
echo "Compiling $cpp_file with additional flags: $@"
if ! g++ -o "$executable" "$cpp_file" "$@" 2> compile_errors.txt; then
    echo "Compilation failed. Here are the errors:"
    cat compile_errors.txt
    rm compile_errors.txt  # Clean up the error file
    exit 1
fi

# Run the resulting executable
echo "Running $executable ..."
./"$executable"

# Clean up the executable (optional)
# Uncomment the line below if you want to remove the executable after running
# rm "$executable"

exit 0
