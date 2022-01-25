# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 12:49:33 by sreinhol          #+#    #+#              #
#    Updated: 2022/01/24 22:22:28 by sreinhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell
HEADER_DIR := ./include/
FLAGS = -Wall -Wextra -Werror -g -I$(HEADER_DIR)
#debug flag use

SRC_DIR := ./src/
OBJ_DIR := ./obj/
SRC = $(SRC_DIR)*.c ./src/linked_lists/*.c ./src/builtins/*.c

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRC))

HEADERS := $(HEADER_DIR)*.h
LIBFT_DIR := /libs/libft/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_OBJS := $(LIBFT_DIR)*.o
GREEN := \033[0;32m
YELLOW := \033[1;33m
RED := \033[1;31m
DEFAULT := \033[0m
LFR= -L$$HOME/.brew/opt/readline/lib -lreadline
LFRC = -I$$HOME/.brew/opt/readline/include

all: $(NAME)

link:
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJ_DIR) $(OBJS) $(HEADERS) link $(LIBFT)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $@
	@echo "\n$(GREEN)$(NAME) created$(DEFAULT)"

	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_DIR)*.o
	@make clean -C $(LIBFT_DIR)
	@echo "\n$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@rm -f ./libs/libft/libft.a
	@echo "\n$(RED)all deleted!$(DEFAULT)"

re: fclean all

no: 
	@$(CC) -o $(NAME) $(SRC) $(LFR) $(LFRC) -L ./libs -lft

.PHONY: all clean fclean re
