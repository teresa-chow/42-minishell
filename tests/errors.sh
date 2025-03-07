#!/bin/bash

clear

printf "\n\033[1;36m --- bash error messages ---\n\033[0m"
printf "\n\033[2;37m ** non-existent cmd **\033[0m"
printf "\n\033[0;33magdagf\n\033[0m"
printf "agdagf: command not found\n"

printf "\n\033[0;33magdagf agdagf\n\033[0m"
printf "agdagf: command not found\n"

printf "\n\n\033[2;37m ** builtins: cd **\033[0m"
printf "\n\033[0;33mcd nonexistentdir\n\033[0m"
printf "bash: cd: nonexistentdir: No such file or directory\n"

printf "\n\033[0;33mchmod 000 dir\ncd dir\n\033[0m"
printf "bash: cd: dir: Permission denied\n"

printf "\n\n\033[2;37m ** builtins: pwd (man pwd for valid options) **\033[0m"
printf "\n\033[0;33mpwd -o\n\033[0m"
printf "pwd: bad option: -o\n"

printf "\n\n\033[2;37m ** builtins: export **\033[0m"
printf "\n\033[0;33mexport ARG = \"value\"\n\033[0m"
printf "bash: export: \`=\': not a valid identifier\n"

printf "\n\n\033[2;37m ** operators **\033[0m"
printf "\n\033[0;33mecho \"hello world\" &&& > new_file\n\033[0m"
printf "bash: syntax error near unexpected token \`\&\'\n"
# echo "hello world" &&& > new_file

printf "\n\033[0;33mecho \"hello world\" &&| new_file\n\033[0m"
printf "bash: syntax error near unexpected token \`\|\'\n"
# echo "hello world" &&| new_file

# non-error scenarios
printf "\n\n\n\033[1;36m --- additional behavior (no error msg) ---\n\033[0m"
printf "\n\033[2;37m ** builtins: pwd **\033[0m"
printf "\n\033[0;33mpwd jfjsdhfjkhs djwefwohrf\n\033[0m"
pwd jfjsdhfjkhs djwefwohrf

printf "\n\033[2;37m ** builtins: export **\033[0m"
printf "\n\033[0;33mexport ARG="arg1" "arg2"\necho \$ARG\n\033[0m"
export ARG="arg1" "arg2"
printf "\033[2;37mconsiders only the first argument\n\033[0m"
echo $ARG

printf "\n\033[0;33mexport ARG=="value"\necho \$ARG\n\033[0m"
export ARG=="value"
echo $ARG

printf "\n\033[0;33mexport ARG= "value"\necho \$ARG\n\033[0m"
export ARG= "value"
printf "\033[2;37mempty variable\n\033[0m"
echo $ARG

printf "\n\033[0;33mexport arg\n\033[0m"
export arg
printf "\033[2;37mempty variable\n\033[0m"
echo $arg

# cat | cat | ls
# ^C