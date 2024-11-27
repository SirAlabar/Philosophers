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

# Colors for pretty output
GREEN = \033[1;32m
RED = \033[0;31m
RESET = \033[0m
CYAN = \033[0;36m

# Project settings
NAME = philo
BONUS_NAME  = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

# Directories
SRCS_DIR = src
BONUS_SRCS_DIR	= srcs_bonus
INCS_DIR = include
OBJ_DIR = obj
BONUS_OBJ_DIR	=	obj_bonus

# Source files - add your .c files here
SRCS = $(addprefix $(SRCS_DIR)/, \
	main.c \
	init.c \
	utils.c \
	check_args.c \
	routines.c \
	status.c \
	monitor.c \
	time.c)

BONUS_SRCS  = $(addprefix $(SRCS_DIR)/, \
			main_bonus.c \
            init_bonus.c \
            check_args_bonus.c \
            monitor_bonus.c \
            routine_bonus.c \
            time_bonus.c \
            utils_bonus.c)

# Object files
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  = $(BONUS_SRCS:$(BONUS_SRCS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# Headers
INCS = -I$(INCS_DIR)

# Default target
all: $(NAME)

# Create object directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile objects
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(CYAN)Compiling $<...$(RESET)"

# Link the final executable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled!$(RESET)"
	@echo "$(RED)𓄿 𓅓 Made by Alabar 𓄿 𓅓$(RESET)"

$(BONUS_NAME): $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)$(BONUS_NAME) successfully compiled!$(RESET)"
	@echo "$(RED)𓄿 𓅓 Made by Alabar 𓄿 𓅓$(RESET)"

# Bonus target
bonus: $(BONUS_NAME)

# Clean object files
clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)Object files deleted$(RESET)"

# Full cleanup
fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable deleted$(RESET)"

# Rebuild everything
re: fclean all

# Run with valgrind for memory leak checking
# Thread checking with Helgrind
leak: all
	valgrind --tool=helgrind ./$(NAME) 4 410 200 200

# Memory leak checking
memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --verbose ./$(NAME) 4 410 200 200

.PHONY: all clean fclean re leak