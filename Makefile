# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchow-so <tchow-so@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 14:47:48 by tchow-so          #+#    #+#              #
#    Updated: 2025/02/14 15:11:59 by tchow-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

# ============================================================================ #
# FILES                                                                        #
# ============================================================================ #

SRC		= $(addprefix $(SRC_DIR)/, main.c input_read.c tokenizer.c echo.c)
OBJS	 	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRC:.c=.o)))
LIBFT_ARC	= $(LIBFT_DIR)/libft.a


# ============================================================================ #
# PATHS                                                                        #
# ============================================================================ #

INC_DIR			= include
SRC_DIR 		= src
BUILTINS_DIR	= builtins/echo

BUILD_DIR		= .build
LIB_DIR			= lib

# Libraries
LIBFT_DIR	= $(LIB_DIR)/libft


# ============================================================================ #
# COMPILER, FLAGS & COMMANDS                                                   #
# ============================================================================ #

CC	= cc
CFLAGS	=  -Wall -Wextra -Werror -lreadline
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

$(NAME): $(LIBFT_ARC) $(BUILD_DIR) $(OBJS)
	@printf "$(GRN)>> Generated object files$(NC)\n\n"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_ARC) -o $(NAME) $(RLFLAGS)
	@printf "$(GRN)>> Compiled minishell$(NC)\n\n"

$(BUILD_DIR):
	$(MKDIR) $(BUILD_DIR)
	@printf "$(GRN)>> Created .build/ directory for object files$(NC)\n\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Library directories
$(LIBFT_DIR):
	git clone https://github.com/teresa-chow/42-libft-extended.git libs/libft
	@printf "$(GRN)>> Cloned Libft$(RES)\n\n"

# Library archives
$(LIBFT_ARC): $(LIBFT_DIR)
	$(MAKE) $(LIBFT_DIR)
	@printf "$(GRN)>> Created Libft archive$(RES)\n\n"


##@ CLEAN-UP RULES

clean:	## Remove object files
	$(RM) $(BUILD_DIR)
	$(MAKE) $(LIBFT_DIR) clean
	@printf "$(GRN)>> Removed object files$(NC)\n\n"

fclean: clean	## Remove executable files
	$(RM) $(NAME)
	@printf "$(GRN)>> Removed executable files$(NC)\n\n"
	$(MAKE) $(LIBFT_DIR) fclean
	@printf "$(GRN)>> Removed Libft archive$(RES)\n\n"

re: fclean all	## Purge and recompile


##@ STANDARD COMPLIANCE CHECK

norm:	## Execute norminette
	norminette $(INC_DIR)
	norminette $(SRC_DIR)


##@ MEMORY MANAGEMENT: DEBUGGING & LEAK DETECTION

valgrind:	## Run valgrind (suppress readline() memory leaks)
	echo "" > rl.supp
	@printf "$(GRN)>> Created rl.supp file\n\n"
	valgrind --leak-check=full --show-leak-kinds=all --track-origin=yes \
	--supressions=rl.supp --track-fds=yes --trace-children=yes ./$(NAME)


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
