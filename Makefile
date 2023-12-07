# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiaferna <tiaferna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 07:44:06 by tiaferna          #+#    #+#              #
#    Updated: 2023/12/07 11:14:48 by tiaferna         ###   ########.fr        #
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

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LFLAGS = -L$(LIBFT_DIR) -lft -lreadline

RM = rm -rf

SRCDIR = src/mandatory

LIBFT_DIR =  src/libft

SRCS = 	src/mandatory/lexer.c src/mandatory/lexer_split.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
	clear
	@echo "$(GREEN)./minishell executable is ready!$(RESET)"

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -I . -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
	clear
	@echo "$(RED)Object files have been deleted!$(RESET)"

fclean: clean
	$(MAKE) -s -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	clear
	@echo "$(RED)Object files and executable have been deleted!$(RESET)"

re: fclean all

.PHONY: all clean fclean re