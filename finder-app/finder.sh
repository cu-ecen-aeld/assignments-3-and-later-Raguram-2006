#!/bin/bash

# Check if both arguments are provided
if [ $# -lt 2 ]; then
    echo "Error: Two arguments required: <dir-path> <search-string>"
    exit 1
fi

filesdir=$1
searchstr=$2

# Check if the directory exists
if [ ! -d "$filesdir" ]; then
    echo "Error: $filesdir is not a directory on the filesystem."
    exit 1
fi

# Count the number of files
X=$(find "$filesdir" -type f | wc -l)

# Count the number of matching lines
Y=$(grep -r "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $X and the number of matching lines are $Y"
