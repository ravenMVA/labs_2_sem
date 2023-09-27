#!/bin/bash

if [$# -ne 2]; then
echo "Using: $0 <suffix> <length[byte]>"
exit 1
fi

suff = "$1"
length = "$2"

echo "Expansion of files: $suff"
echo "Required size: $length bytes"

