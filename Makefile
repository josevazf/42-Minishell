# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiago <tiago@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 07:44:06 by tiaferna          #+#    #+#              #
#    Updated: 2024/03/07 11:00:56 by tiago            ###   ########.fr        #
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
					minishell_utils.c \
					structs_init.c \
					lexer/lexer_main.c \
					lexer/lexer_split.c \
					lexer/lexer_split_utils.c \
					lexer/lexer_elements.c \
					lexer/lexer_quotes_checker.c \
					expander/expander.c \
					expander/eof_handler.c \
					expander/macros_tools.c \
					parser/parser_main.c \
					parser/parser_cmd.c \
					parser/parser_utils.c \
					executer/executer_heredoc_expander.c \
					executer/executer_main.c \
					executer/executer_utils.c \
					executer/executer_single_cmd.c \
					executer/executer_multi_cmds.c \
					executer/executer_multi_redirs.c \
					executer/executer_multi_utils.c \
					executer/executer_redirs_utils.c \
					builtins/cd.c \
					builtins/env_main.c \
					builtins/env.c \
					builtins/exit_shell.c \
					builtins/echo.c \
					builtins/export.c \
					builtins/export_utils.c \
					builtins/unset.c \
					builtins/pwd.c \
					builtins/new_var_set.c \
					signals.c \
					free_mem.c \
					error_1.c \
					error_2.c \
					print_utils.c \
					envp_tools.c

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

#testing fd leaks
leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

readline.supp:
	@echo "{" > readline.supp
	@echo "    leak readline" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:readline" >> readline.supp
	@echo "}" >> readline.supp
	@echo "{" >> readline.supp
	@echo "    leak add_history" >> readline.supp
	@echo "    Memcheck:Leak" >> readline.supp
	@echo "    ..." >> readline.supp
	@echo "    fun:add_history" >> readline.supp
	@echo "}" >> readline.supp

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	$(RM) $(NAME) $(LIBFT) readline.supp

#reset environment - remove everything and recompile
re: fclean
	$(MAKE) all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
.SILENT: