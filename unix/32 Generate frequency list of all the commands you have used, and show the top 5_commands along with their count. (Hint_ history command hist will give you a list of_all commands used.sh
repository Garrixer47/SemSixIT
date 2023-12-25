#!/bin/bash

# Get the command history
history | awk '{$1=""; print $0}' | sed -e 's/^[[:space:]]*//' > command_history.txt

# Generate the frequency list
command_frequency=$(cat command_history.txt | tr ' ' '\n' | sort | uniq -c | sort -nr)

# Display the top 5 commands
echo "Top 5 Commands:"
echo "$command_frequency" | head -n 5
