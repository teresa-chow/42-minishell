#!/bin/bash
# =========================================================================== #
# minishell tester                                                            #
# by Teresa Chow (tchow-so) and Carlos Teixeira (carlaugu)                    #
# Created on: 2025-05-15                                                      #
# =========================================================================== #

# PATHS, TOOLS AND SETUP
MINISHELL="../minishell"
VALGRIND="valgrind --leak-check=full --show-leak-kinds=all \
    --suppressions=rl.supp --track-fds=yes --error-exitcode=257"
TMP_DIR="./tmp"
TEST_FILES="./test_files"
SHOW_OUTPUT="false" # Set to 'true' to display outputs

mkdir -p "$TMP_DIR"

# -----------------------------------------------------------------------------
# UTILS: TEST FILES
mkdir -p "$TEST_FILES"
mkdir -p $TEST_FILES/folder_no_permission
chmod 000 $TEST_FILES/folder_no_permission

# -----------------------------------------------------------------------------
# UTILS: ANSI COLOR SEQUENCES

# Reset to default
NC='\033[0m'

# Regular text colors
RED="\033[0;31m"
GRN='\033[0;32m'
YEL="\033[0;33m"
BLU="\033[0;34m"
MAG="\033[0;35m"
CYA="\033[0;36m"
WHI="\033[0;37m"

# Bold text colors
RED_B="\033[1;31m"
GRN_B="\033[1;32m"
YEL_B="\033[1;33m"
BLU_B="\033[1;34m"
MAG_B="\033[1;35m"
CYA_B="\033[1;36m"
WHI_B="\033[1;37m"

# Bold text background colors
GRN_BG="\033[1;42m"
CYA_BG="\033[1;46m"

# -----------------------------------------------------------------------------
# BUILTINS TEST LISTS
ECHO_TESTS=(
  'echo'
  'echo -n'
  'echo Hello World!'
  'echo      Hello     World!      '
  'echo -n No newline'
  'echo -nnnnnn No newline'
  'echo -n -n -n -n No newline'
  'echo -na Hello World!'
  'echo -n No newline -n'
  'echo ""'
  "echo ''"
  'echo " "'
)

CD_TESTS=(
  'cd && pwd'
  'cd . && pwd'
  'cd /tmp && pwd'
  'cd / && pwd'
  'cd .. && pwd'
  'cd ~ && pwd'
  'cd - && pwd'
  'cd non_existing_dir'
  'cd tmp tmp'
  'cd test_files/folder_no_permission'
)

PWD_TESTS=(
  'pwd'
  'pwd arg'
)

EXPORT_TESTS=(
  'export VAR=123 && export | grep "VAR"'
  'export VAR && export | grep "VAR"'
  'export VAR && export | grep "VAR"'
  'export VAR="" && export | grep "VAR"'
  'export USER+="123" && export | grep "USER"'
  'export VAR=="value" && export | grep "VAR"'
  'export +='
)

ENV_TESTS=(
  'env | grep USER'
  'export VAR && env | grep VAR'
  'export VAR= && env | grep VAR'
)

UNSET_TESTS=(
  'export VAR="val" && unset VAR && env | grep VAR'
)

EXIT_TESTS=(
  'exit'
  'exit 0'
  'exit 1'
  'exit 257'
  'exit +123'
  'exit -123'
  'exit a'
  'exit 1 1'
  'exit 999999999999999999999999999999999999'
)

BUILTINS=("ECHO" "CD" "PWD" "EXPORT" "ENV" "UNSET" "EXIT")

# -----------------------------------------------------------------------------
# GENERAL TESTS
QUOTES_TESTS=(
  'export VAR="ls -la" && $VAR'
  'export VAR="ls -la" && "$VAR"'
  'echo "$USER"'
  "echo '$USER'"
  'echo "Hello                      World"'
)

#SIGNALS_TESTS=(
#  'kill -SIGINT'
#  'kill -SIGQUIT'
#)

PATHS_TESTS=(
  'ls'
  'unset PATH && ls'
)

#ENVIRONMENT_TESTS=(
#
#)

#REDIRECTION_TESTS=(
#
#)

PIPES_TESTS=(
  'echo hello | cat -e'
  'xxx | echo hello'
  'echo hello | yyy | ls'
  'ls fail | echo hello'
)

GENERAL=("QUOTES" "SIGNALS" "PATHS" "ENVIRONMENT" "REDIRECTION" "PIPES")

clear
printf ${YEL}
echo "▖  ▖▘  ▘  ▌   ▜ ▜   ▄▖    ▗     ";
echo "▛▖▞▌▌▛▌▌▛▘▛▌█▌▐ ▐   ▐ █▌▛▘▜▘█▌▛▘";
echo "▌▝ ▌▌▌▌▌▄▌▌▌▙▖▐▖▐▖  ▐ ▙▖▄▌▐▖▙▖▌ ";
echo
echo "by Teresa Chow (tchow-so) & Carlos Teixeira (carlaugu)"
printf ${NC}
# -----------------------------------------------------------------------------
# TEST BY BUILTIN
for builtin in "${BUILTINS[@]}"; do
  tests_var="${builtin}_TESTS[@]"
  test_list=("${!tests_var}")

  printf "\n${CYA_BG} ${builtin,,} ${NC} ${CYA}(builtin)${NC}\n"

  for cmd in "${test_list[@]}"; do
    # bash output
    bash -c "$cmd" >"$TMP_DIR/bash_stdout" 2>"$TMP_DIR/bash_stderr"
    bash_exit=$?

    # minishell output with valgrind
    $VALGRIND "$MINISHELL" < <(echo "$cmd") >"$TMP_DIR/ms_stdout_raw" 2>"$TMP_DIR/ms_stderr_raw"
    ms_exit=$?
    valgrind_status=$?
    # filter valgrind info from stderr 
    grep -v '^==.*==' "$TMP_DIR/ms_stderr_raw" > "$TMP_DIR/ms_stderr"
    
    # clean minishell stdout (remove ANSI sequences) 
    tail -n +2 "$TMP_DIR/ms_stdout_raw" | sed -E 's/\x1B\[[0-9;]*[a-zA-Z]//g' > "$TMP_DIR/ms_stdout"

    # diff check
    diff -u "$TMP_DIR/bash_stdout" "$TMP_DIR/ms_stdout" >"$TMP_DIR/diff_stdout"
    diff -u "$TMP_DIR/bash_stderr" "$TMP_DIR/ms_stderr" >"$TMP_DIR/diff_stderr"

    # show outputs
    if [ "$SHOW_OUTPUT" = true ]; then
      echo -n "Minishell (stdout): "; cat "$TMP_DIR/ms_stdout"
      echo -n "Bash (stdout): "; cat "$TMP_DIR/bash_stdout"
      echo -n "Minishell (stderr): "; cat "$TMP_DIR/ms_stderr"
      echo -n "Bash (stderr): "; cat "$TMP_DIR/bash_stderr"
    fi

    # result logic
    if [ "$valgrind_status" -eq 257 ]; then
      printf "${RED}🗶 KO (memory leak): ${NC}"
    elif [ "$bash_exit" -ne "$ms_exit" ]; then
      printf "${RED}🗶 KO (exit code — bash=$bash_exit vs minishell=$ms_exit): ${NC}"
    elif [ -s "$TMP_DIR/diff_stdout" ]; then
      printf "${RED}🗶 KO (output): ${NC}"
    elif [ -s "$TMP_DIR/diff_stderr" ]; then
      printf "${YEL}◉ Error case (stderr msgs): ${NC}"
    else
      printf "${GRN}✔ OK: ${NC}"
    fi
    echo $cmd
    if [ -s "$TMP_DIR/diff_stdout" ]; then
      [ -s "$TMP_DIR/diff_stdout" ] && cat "$TMP_DIR/diff_stdout"
    elif [ -s "$TMP_DIR/diff_stderr" ]; then
      printf "\t${YEL}bash:\t\t${NC}"; cat "$TMP_DIR/bash_stderr"
      printf "\t${YEL}minishell:\t${NC}"; cat "$TMP_DIR/ms_stderr"
    fi
  done
done

# -----------------------------------------------------------------------------
# GENERAL TESTS
for general in "${GENERAL[@]}"; do
  tests_var="${general}_TESTS[@]"
  test_list=("${!tests_var}")

  printf "\n${GRN_BG} ${general,,} ${NC} ${GRN}(general)${NC}\n"

  for cmd in "${test_list[@]}"; do
    # bash output
    bash -c "$cmd" >"$TMP_DIR/bash_stdout" 2>"$TMP_DIR/bash_stderr"
    bash_exit=$?

    # minishell output with valgrind
    $VALGRIND "$MINISHELL" < <(echo "$cmd") >"$TMP_DIR/ms_stdout_raw" 2>"$TMP_DIR/ms_stderr_raw"
    ms_exit=$?
    valgrind_status=$?
    # filter valgrind info from stderr 
    grep -v '^==.*==' "$TMP_DIR/ms_stderr_raw" > "$TMP_DIR/ms_stderr"
    
    # clean minishell stdout (remove ANSI sequences) 
    tail -n +2 "$TMP_DIR/ms_stdout_raw" | sed -E 's/\x1B\[[0-9;]*[a-zA-Z]//g' > "$TMP_DIR/ms_stdout"

    # diff check
    diff -u "$TMP_DIR/bash_stdout" "$TMP_DIR/ms_stdout" >"$TMP_DIR/diff_stdout"
    diff -u "$TMP_DIR/bash_stderr" "$TMP_DIR/ms_stderr" >"$TMP_DIR/diff_stderr"

    # show outputs
    if [ "$SHOW_OUTPUT" = true ]; then
      echo -n "Minishell (stdout): "; cat "$TMP_DIR/ms_stdout"
      echo -n "Bash (stdout): "; cat "$TMP_DIR/bash_stdout"
      echo -n "Minishell (stderr): "; cat "$TMP_DIR/ms_stderr"
      echo -n "Bash (stderr): "; cat "$TMP_DIR/bash_stderr"
    fi

    # result logic
    if [ "$valgrind_status" -eq 257 ]; then
      printf "${RED}🗶 KO (memory leak): ${NC}"
    elif [ "$bash_exit" -ne "$ms_exit" ]; then
      printf "${RED}🗶 KO (exit code — bash=$bash_exit vs minishell=$ms_exit): ${NC}"
    elif [ -s "$TMP_DIR/diff_stdout" ]; then
      printf "${RED}🗶 KO (output): ${NC}"
    elif [ -s "$TMP_DIR/diff_stderr" ]; then
      printf "${YEL}◉ Error case (stderr msgs): ${NC}"
    else
      printf "${GRN}✔ OK: ${NC}"
    fi
    echo $cmd
    if [ -s "$TMP_DIR/diff_stdout" ]; then
      [ -s "$TMP_DIR/diff_stdout" ] && cat "$TMP_DIR/diff_stdout"
    elif [ -s "$TMP_DIR/diff_stderr" ]; then
      printf "\t${YEL}bash:\t\t${NC}"; cat "$TMP_DIR/bash_stderr"
      printf "\t${YEL}minishell:\t${NC}"; cat "$TMP_DIR/ms_stderr"
    fi
  done
done

rm -rf $TEST_FILES
rm -rf $TMP_DIR