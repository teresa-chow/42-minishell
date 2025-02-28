#!/bin/bash

printf "\033[0;33mecho \"Hello\"\n\033[0m"
echo "Hello"

printf "\n\033[2;37mprint without newline\033[0m"
printf "\n\033[0;33mecho -n \"Hello\"\n\033[0m"
echo -n "Hello"

printf "\n\033[0;33mecho -n -n \"Hello\"\n\033[0m"
echo -n -n "Hello"

printf "\n\033[0;33mecho -nnnn \"Hello\"\n\033[0m"
echo -nnnn "Hello"

printf "\n\n\033[2;37mprints literal\033[0m"
printf "\n\033[0;33mecho -na \"Hello\"\n\033[0m"
echo -na "Hello"

printf "\n\033[0;33mecho\n\033[0m"
printf "\033[2;37mprints newline\n\033[0m"
echo

printf "\033[0;33mexport ARG=Hello\033[0m"
printf '\n\033[0;33mecho $ARG\n\033[0m'
printf "\033[2;37mexport variable and print value\n\033[0m"
export ARG=Hello
echo $ARG
printf "\n\033[0;33munset ARG\033[0m"
printf '\n\033[0;33mecho $ARG\n\033[0m'
printf "\033[2;37munset variable and print value – prints newline\n\033[0m"
unset ARG
echo $ARG