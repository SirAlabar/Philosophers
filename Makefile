# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hluiz-ma <hluiz-ma@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 19:22:40 by hluiz-ma          #+#    #+#              #
#    Updated: 2024/11/26 21:00:00 by hluiz-ma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		= \033[1;32m
RED			= \033[0;31m
RESET		= \033[0m
CYAN		= \033[0;36m

# Compilation
NAME		= philo
BONUS_NAME	= philo_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -rf

# Directories
SRCS_DIR	= src
BONUS_DIR	= src_bonus
INCS_DIR	= include
OBJ_DIR		= obj
BONUS_OBJ	= obj_bonus

# Mandatory source files
SRCS		= $(addprefix $(SRCS_DIR)/, \
			main.c \
			init.c \
			utils.c \
			check_args.c \
			routines.c \
			status.c \
			monitor.c \
			time.c)

# Bonus source files
BONUS_SRCS	= $(addprefix $(BONUS_DIR)/, \
			main_bonus.c \
			init_bonus.c \
			check_args_bonus.c \
			monitor_bonus.c \
			routine_bonus.c \
			status_bonus.c \
			time_bonus.c \
			utils_bonus.c)

# Object files
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS	= $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ)/%.o)

# Headers
INCS		= -I$(INCS_DIR)

# Default target
all: $(NAME)

# Bonus target
bonus: $(BONUS_NAME)

# Create directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BONUS_OBJ):
	@mkdir -p $(BONUS_OBJ)

# Mandatory compilation
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(CYAN)Compiling $<...$(RESET)"

# Bonus compilation
$(BONUS_OBJ)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(CYAN)Compiling bonus $<...$(RESET)"

# Linking
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled!$(RESET)"
	@echo "$(RED)𓄿 𓅓 Made by Alabar 𓄿 𓅓$(RESET)"

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)$(BONUS_NAME) successfully compiled!$(RESET)"
	@echo "$(RED)𓄿 𓅓 Made by Alabar 𓄿 𓅓$(RESET)"

# Cleaning
clean:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(BONUS_OBJ)
	@echo "$(RED)Object files deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@echo "$(RED)Executables deleted$(RESET)"

# Rebuild
re: fclean all
re_bonus: fclean bonus

# Debug and testing
leak: all
	valgrind --tool=helgrind ./$(NAME) 4 410 200 200

leak_bonus: bonus
	valgrind --tool=helgrind ./$(BONUS_NAME) 4 410 200 200

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --verbose ./$(NAME) 4 410 200 200

memcheck_bonus: bonus
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --verbose ./$(BONUS_NAME) 4 410 200 200

# Phony targets
.PHONY: all bonus clean fclean re re_bonus leak leak_bonus memcheck memcheck_bonus