#!/bin/bash

# Prompt the user to enter the file path
read -p "Enter the file path: " filepath

# Check if the file exists
if [ -e "$filepath" ]; then
    echo "File '$filepath' exists."
else
    echo "File '$filepath' does not exist."
fi
