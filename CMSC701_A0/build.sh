#!/bin/bash

# Set the source file and output executable name
SOURCE_FILE="fasta_stats.cpp"
OUTPUT_FILE="fasta_stats"

# Compile using g++
# g++ -std=c++17 -Wall -Wextra -o $OUTPUT_FILE $SOURCE_FILE
g++ -std=c++17 -o $OUTPUT_FILE $SOURCE_FILE

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Run ./$OUTPUT_FILE"
else
    echo "Compilation failed!"
fi