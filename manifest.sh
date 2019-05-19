#!/bin/bash
# Subtree manifest, to be sourced into other
# scripts where needed.

branch=master

declare -A manifest=(
    [submods/merseburg-incantation]=https://github.com/flajann2/merseburg-incantation.git
)

## example of looping through the array
#for dir in "${!manifest[@]}"; do
#    echo "$dir <== ${manifest[$dir]}"
#done
