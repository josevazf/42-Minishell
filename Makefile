# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 07:44:06 by tiaferna          #+#    #+#              #
#    Updated: 2023/12/29 12:20:56 by tiaferna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

RESET	= \033[0m
BOLD	= \033[1m
FAINT	= \033[2m
ITALIC	= \033[3m
ULINE	= \033[4m
SBLINK	= \033[5m
FBLINK	= \033[6m
REVCOL	= \033[7m
HIDDEN	= \033[8m
CROSS	= \033[9m
BLACK   = \033[1;30m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
PURPLE  = \033[1;35m
CYAN    = \033[1;36m
WHITE   = \033[1;37m

SRCS_DIR		= src

OBJS_DIR		= objs

INCLUDES		= includes
LIBFT			= ./libs/libft/libft.a
LIBFT_DIR		= ./libs/libft

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g 
RM				= rm -rf

SRCS			= 	minishell.c \
					env_main.c \
					lexer_main.c \
					lexer_split.c \
					lexer_cmd.c \
					lexer_elements.c \
					lexer_quotes_checker.c \
					expander.c \
					ft_strndup.c \
					free_mem.c \
					error.c \
					cd.c \
					pwd.c

# Substitute .c with .o 
OBJS			= $(SRCS:%.c=$(OBJS_DIR)/%.o)

#default target
all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)./minishell executable is ready!$(RESET)"

#create .o fies
# $< first prerequisite aka .c; $@ output/target file aka .o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBFT):
	clear
	@echo "$(YELLOW)Compiling necessary libs...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	$(RM) $(NAME) $(LIBFT)

#reset environment - remove everything and recompile
re: fclean
	$(MAKE) all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
.SILENT: