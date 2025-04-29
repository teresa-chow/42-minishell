# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 14:47:48 by tchow-so          #+#    #+#              #
#    Updated: 2025/04/29 10:59:25 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
BONUS		= minishell_bonus

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC				= $(addprefix $(SRC_DIR)/, main.c)
SRC_PARSER		= $(addprefix $(PARSER_DIR)/, read_input.c read_input_prompt.c \
	tokenize_op.c tokenize_div.c tokenize_div_parentheses.c \
	tokenize_div_quotes.c tokenize_div_redirect.c tokenize_div_general.c \
	tokenize_utils.c syntax_analysis.c syntax_analysis_parentheses.c \
	syntax_analysis_utils.c syntax_tree.c syntax_tree_utils.c)
SRC_EXECUTER	= $(addprefix $(EXECUTER_DIR)/, exec_ast.c exec_ast_utils.c \
	exec_ast_pipeline.c exec_ast_pipeline_utils.c redir_check.c heredoc.c \
	redir_utils.c redir_in.c redir_out.c redir_out_utils.c)
SRC_BUILTINS	= $(addprefix $(BUILTINS_DIR)/, cd.c echo.c env.c exit.c \
	exit_utils.c export.c export_utils.c export_utils2.c export_merge_sort.c \
	pwd.c unset.c builtins_utils.c builtins_utils_2.c)
SRC_EXECVE		= $(addprefix $(EXECVE_DIR)/, exec.c execve_utils.c)
SRC_UTILS		= $(addprefix $(UTILS_DIR)/, mem_utils.c mem_utils2.c \
	init_env.c set_path.c print_fd.c utils.c)
SRC_EXPANDER	= $(addprefix $(EXPANDER_DIR)/, expand_env_handle.c \
	expand_tilde.c expand_val_split.c handle_tokens_main.c \
	handle_tokens_utils.c string_tword_builder.c token_checkers.c \
	token_expansion_analyze.c handle_tokens_utils2.c wildcards_analyze.c \
	wildcards_check_match.c wildcards_utils.c wildcards_utils2.c \
	wildcards_utils3.c quote_removal.c)
SRC_ERRORS		= $(addprefix $(ERRORS_DIR)/, handle_err.c handle_err2.c \
	handle_err3.c)
TEST			= $(addprefix $(TEST_DIR)/, test.c) #delete

OBJS	 		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
OBJS_PARSER	 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_PARSER:.c=.o)))
OBJS_EXECUTER 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_EXECUTER:.c=.o)))
OBJS_BUILTINS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_BUILTINS:.c=.o)))
OBJS_EXECVE		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_EXECVE:.c=.o)))
OBJS_UTILS		= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_UTILS:.c=.o)))
OBJS_EXPANDER	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC_EXPANDER:.c=.o)))
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

EXPANDER_DIR	= $(SRC_DIR)/expander

BUILTINS_DIR	= $(SRC_DIR)/builtins

EXECVE_DIR		= $(SRC_DIR)/execve

UTILS_DIR		= $(SRC_DIR)/utils

EXECUTER_DIR 	= $(SRC_DIR)/executer

ERRORS_DIR		= $(SRC_DIR)/errors

TEST_DIR		= tests

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

bonus: $(BONUS)

$(NAME): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS) $(OBJS_PARSER) $(OBJS_EXECUTER) \
	$(OBJS_BUILTINS) $(OBJS_EXECVE) $(OBJS_UTILS) $(OBJS_EXPANDER) \
	$(OBJS_ERRORS) $(OBJS_TEST)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PARSER) $(OBJS_EXECUTER) $(OBJS_BUILTINS) \
	$(OBJS_EXECVE) $(OBJS_UTILS) $(OBJS_EXPANDER) $(OBJS_ERRORS) $(OBJS_TEST) \
	$(LIBFT_ARC) -o $(NAME) $(RLFLAGS)
	@printf "$(GRN)>> Compiled minishell$(NC)\n\n"

$(BONUS): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS) $(OBJS_PARSER) $(OBJS_EXECUTER) \
	$(OBJS_BUILTINS) $(OBJS_EXECVE) $(OBJS_UTILS) $(OBJS_EXPANDER) \
	$(OBJS_ERRORS) $(OBJS_TEST)
	@printf "$(GRN)>> Generated object files (bonus)$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_PARSER) $(OBJS_EXECUTER) $(OBJS_BUILTINS) \
	$(OBJS_EXECVE) $(OBJS_UTILS) $(OBJS_EXPANDER) $(OBJS_ERRORS) $(OBJS_TEST) \
	$(LIBFT_ARC) -o $(BONUS) $(RLFLAGS)
	@printf "$(GRN)>> Compiled minishell (bonus)$(NC)\n\n"


$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(PARSER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXECUTER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(BUILTINS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXECVE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(EXPANDER_DIR)/%.c
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
	$(RM) $(NAME) $(BONUS)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(NC)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR) $(LIB_DIR) $(SRC_DIR)


##@ MEMORY MANAGEMENT: DEBUGGING & LEAK DETECTION

vg: all	## Run valgrind (suppress readline() memory leaks)
	$(file > rl.supp, $(RL_SUPP))
	@printf "$(GRN)>> Created rl.supp file\n\n$(NC)"
	valgrind --leak-check=full --show-leak-kinds=all \
	--suppressions=rl.supp --track-fds=yes \
	./$(NAME)
#--log-file=memleaks.log


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
# UTILS: READLINE LEAKS SUPPRESSION FILE                                       #
# ============================================================================ #

define RL_SUPP
{
	rl lib
	Memcheck:Leak
	fun:*alloc
	...
	obj:*/libreadline.so.*
	...
}
{
	rl fun
	Memcheck:Leak
	...
	fun:readline
}
{
	rl add_history
	Memcheck:Leak
	...
	fun:add_history
}
endef

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
