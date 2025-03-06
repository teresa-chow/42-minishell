#!/bin/bash

clear

printf "\n\033[1;36m --- empty environment behavior ---\n\033[0m"
printf "\n\033[0;33menv -i bash\nexport\n\033[0m"
printf "declare -x OLDPWD\n"
printf "declare -x PWD=\"/home/tchow-so/Documents/42-minishell/tests\"\n"
printf "declare -x SHLVL=\"1\"\n"

printf "\n\033[0;33menv -i bash\nenv\n\033[0m"
printf "declare -x PWD=/home/tchow-so/Documents/42-minishell/tests\n"
printf "declare -x SHLVL=1\n"
printf "_=/usr/bin/env\n"

printf "\n\033[1;36m --- PWD and OLD behavior ---\n\033[0m"
printf "\033[2;37mkeep updating during execution, even with empty environment at start\n\n\033[0m"
printf "\033[0;33munset PWD\n\033[0m"
unset PWD

printf "\033[0;33munset OLDPWD\n\033[0m"
unset OLDPWD

printf "\n\033[0;33mcd ..\necho \$PWD\n\033[0m"
cd ..
echo $PWD
printf "\n\033[0;33mecho \$OLDPWD\n\033[0m"
echo $OLDPWD

printf "\n\033[0;33mcd tests\necho \$PWD\necho \$OLDPWD\n\033[0m"
cd tests
echo $PWD
echo $OLDPWD

printf "\n\033[1;36m --- SHLVL BEHAVIOR ---\n\033[0m"
printf "\033[2;37mwith empty environment starts at 1, if unset remains empty\nshould increment every time minishell is executed\033[0m"
printf "\n\033[0;33mbash\necho \$SHLVL\n\033[0m"
echo $SHLVL

printf "\n\033[0;33menv -i bash\necho \$SHLVL\n\033[0m"
printf "1\n"
# env -i bash
# echo $SHLVL
# exit

printf "\n\033[0;33munset SHLVL\necho \$SHLVL\n\033[0m"
printf "\033[2;37mprint newline\n\n\033[0m"
printf "\n\033[0;33mbash\necho \$SHLVL\n\033[0m"
printf "1\n\n"
# unset SHLVL
# echo $SHLVL
# bash
# echo $SHLVL