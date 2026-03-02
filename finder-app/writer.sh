#!/bin/bash

if [ $# -lt 2]; then
      echo "ERROR: Two arguments required: <full-path-to-file> <text-string>"
      exit 1;
fi
 writefile=$1
 writestr=$2
dirpath=$(dirname "$writefile")
mkdir -p "$dirpath"

# Create or overwrite the file
if echo "$writestr" > "$writefile"; then
    exit 0
else
    echo "Error: File could not be created at $writefile"
    exit 1
fi
