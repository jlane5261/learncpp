#!/bin/bash

# Compile the program
g++ -o TicTacToe main.cpp Game.cpp Board.cpp

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable: TicTacToe"
else
    echo "Compilation failed!"
    exit 1
fi