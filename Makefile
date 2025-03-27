# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlaugu <carlaugu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 14:47:48 by tchow-so          #+#    #+#              #
#    Updated: 2025/03/27 15:07:07 by carlaugu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC				= $(addprefix $(SRC_DIR)/, main.c)
SRC_PARSER		= $(addprefix $(PARSER_DIR)/, read_input.c \
	tokenize_op.c tokenize_div.c tokenize_div_parentheses.c \
	tokenize_div_quotes.c tokenize_div_redirect.c tokenize_div_general.c \
	tokenize_utils.c syntax_analysis.c syntax_analysis_utils.c syntax_tree.c \
	syntax_tree_utils.c)
SRC_BUILTINS	= $(addprefix $(BUILTINS_DIR)/, cd.c echo.c env.c exit.c export.c \
	export_utils.c export_merge_sort.c pwd.c unset.c builtins_utils.c)
SRC_EXECVE	= $(addprefix $(EXECVE_DIR)/, exec.c execve_utils.c)
SRC_UTILS	= $(addprefix $(UTILS_DIR)/, mem_utils.c init_env.c \
	set_path.c print_fd.c)
SRC_ERRORS	= $(addprefix $(ERRORS_DIR)/, handle_err.c handle_err2.c)
TEST			= $(addprefix $(TEST_DIR)/, test.c) #delete

OBJS	 		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
OBJS_PARSER	 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_PARSER:.c=.o)))
OBJS_BUILTINS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_BUILTINS:.c=.o)))
OBJS_EXECVE		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_EXECVE:.c=.o)))
OBJS_UTILS		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_UTILS:.c=.o)))
OBJS_ERRORS		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_ERRORS:.c=.o)))
OBJS_TEST		= $(addprefix $(BUILD_DIR)/, $(notdir $(TEST:.c=.o))) #delete

LIBFT_ARC	= $(LIBFT_DIR)/libft.a


# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

INC_DIR			= include
SRC_DIR 		= src

BUILD_DIR		= .build
LIB_DIR			= lib

# Sources
PARSER_DIR		= $(SRC_DIR)/parser

BUILTINS_DIR	= $(SRC_DIR)/builtins

EXECVE_DIR	= $(SRC_DIR)/execve

UTILS_DIR	= $(SRC_DIR)/utils

ERRORS_DIR	= $(SRC_DIR)/errors

TEST_DIR	= tests

# Libraries
LIBFT_DIR	= $(LIB_DIR)/libft

# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #

CC	= cc
CFLAGS	=  -Wall -Wextra -Werror
CFLAGS	+= -g
RLFLAGS = -lreadline

MAKE	= make -C

RM	= rm -rf
AR	= ar rcs
MKDIR	= mkdir -p

# ============================================================================ #
# RULES                                                                        #
# ============================================================================ #

##@ COMPILATION RULES

all: $(NAME)	## Compile minishell

$(NAME): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS) $(OBJS_PARSER) $(OBJS_BUILTINS) \
	$(OBJS_EXECVE) $(OBJS_UTILS) $(OBJS_ERRORS) $(OBJS_TEST)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
######### ------->>> i add -L/usr/lib/aarch.... because my vm on my pc but it's to delete //////-L/usr/lib/aarch64-linux-gnu -lreadline -lncurses
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PARSER) $(OBJS_BUILTINS) $(OBJS_EXECVE) \
	$(OBJS_UTILS) $(OBJS_ERRORS) $(OBJS_TEST) $(LIBFT_ARC) -o $(NAME) $(RLFLAGS)
	@printf "$(GRN)>> Compiled minishell$(NC)\n\n"


$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXECVE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(ERRORS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Library directories
$(LIBFT_DIR):
	git clone https://github.com/teresa-chow/42-libft-extended.git libs/libft
	@printf "$(GRN)>> Cloned Libft$(NC)\n\n"

# Library archives
$(LIBFT_ARC): $(LIBFT_DIR)
	$(MAKE) $(LIBFT_DIR)
	@printf "$(GRN)>> Created Libft archive$(NC)\n\n"


##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	$(MAKE) $(LIBFT_DIR) clean
	@printf "$(GRN)>> Removed object files$(NC)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(NC)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR) $(LIB_DIR) $(SRC_DIR)


##@ MEMORY MANAGEMENT: DEBUGGING & LEAK DETECTION

valgrind: all	## Run valgrind (suppress readline() memory leaks)
	printf "{\\nignore_libreadline_leaks\\nMemcheck:Leak\\n...\\n \
    obj:*/libreadline.so.*\\n}" > rl.supp
	@printf "$(GRN)>> Created rl.supp file\n\n$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	--suppressions=rl.supp --track-fds=yes --trace-children=yes ./$(NAME)


##@ TOOL INSTALLATION

install: ## Install norminette and valgrind
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y


##@ HELP

help:	## Display this help info
	@awk 'BEGIN { \
		FS = ":.*##"; \
		printf "\n$(WHI_B)USAGE$(NC)\n\t$(YEL)make$(NC)$(CYA)\t \
		<target>$(NC)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
		printf "\t$(CYA_B)%-15s$(NC) %s\n", $$1, $$2 } \
		/^##@/ { printf "\n$(WHI_B)%s$(NC)\n", \
		substr($$0, 5) } ' Makefile
	@printf "\n"

.PHONY: all clean fclean re norm valgrind install help


# ============================================================================ #
# UTILS: SHELL FORMATTING                                                      #
# ============================================================================ #

# Reset to default
NC = \033[0m

# Regular text colors
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHI = \033[0;37m

# Bold text colors
RED_B = \033[1;31m
GRN_B = \033[1;32m
YEL_B = \033[1;33m
BLU_B = \033[1;34m
MAG_B = \033[1;35m
CYA_B = \033[1;36m
WHI_B = \033[1;37m
