# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 12:49:33 by sreinhol          #+#    #+#              #
#    Updated: 2021/12/27 12:50:34 by sreinhol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
HEADER_DIR := ./include/
FLAGS = -Wall -Wextra -Werror -g -I$(HEADER_DIR)

SRC_DIR := ./src/
OBJ_DIR := ./obj/
SRC = ./src/pipex.c ./src/utils.c ./src/free.c ./src/child.c

SRC_BONUS_DIR := ./src_bonus/
OBJ_BONUS_DIR := ./obj_bonus/
SRC_BONUS = ./src_bonus/pipex.c ./src_bonus/utils.c \
	./src_bonus/heredoc.c ./src_bonus/open.c\
	./src_bonus/get_next_line.c ./src_bonus/get_next_line_utils.c

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRC))
OBJS_BONUS := $(patsubst $(SRC_BONUS_DIR)%.c,$(OBJ_BONUS_DIR)%.o, $(SRC_BONUS))

HEADERS := $(HEADER_DIR)*.h
LIBFT_DIR := ../libs/libft/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_OBJS := $(LIBFT_DIR)*.o
GREEN := \033[0;32m
YELLOW := \033[1;33m
RED := \033[1;31m
DEFAULT := \033[0m

all: $(NAME)

link:
	@make -C $(LIBFT_DIR)

$(NAME) : $(OBJ_DIR) $(OBJS) $(HEADERS) link $(LIBFT)
	@gcc $(FLAGS) $(OBJS) $(LIBFT) -o $@
	@echo "\n$(GREEN)$(NAME) created$(DEFAULT)"

bonus: $(OBJ_BONUS_DIR) $(OBJS_BONUS) $(HEADERS) link $(LIBFT)
	@gcc $(FLAGS) $(OBJS_BONUS) $(LIBFT) -o pipex_bonus
	@echo "\n$(GREEN)pipex_bonus created$(DEFAULT)"
	
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(FLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_DIR)*.o $(OBJ_BONUS_DIR)*.o
	@make clean -C $(LIBFT_DIR)
	@echo "\n$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@rm -f ./libs/libft/libft.a
	@rm -f libft.a
	@rm -f pipex
	@rm -f pipex_bonus
	@echo "\n$(RED)all deleted!$(DEFAULT)"

re: fclean all


.PHONY: all clean fclean re bonus       1
