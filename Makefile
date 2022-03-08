CC = gcc
NAME = minishellll
HEADER_DIR := ./include/
FLAGS = -Wall -Wextra -Werror -g -I$(HEADER_DIR)
SRC_DIR := ./src/
OBJ_DIR := ./obj/
SRC = ./src/builtins/cd.c\
./src/builtins/echo.c\
./src/builtins/env.c\
./src/builtins/exit.c\
./src/builtins/export.c\
./src/builtins/export2.c\
./src/builtins/handle_builtins.c\
./src/builtins/pwd.c\
./src/builtins/unset.c\
./src/error/error.c\
./src/error/free.c\
./src/execution/exec_cmd.c\
./src/execution/execution.c\
./src/execution/execution_helpers.c\
./src/expander/expan_no_q_f_heredocfile.c\
./src/expander/expand_functions.c\
./src/linked_lists/add_node_back.c\
./src/linked_lists/list_helpers.c\
./src/linked_lists/new_node.c\
./src/minishell.c\
./src/parser/bypass_directing.c\
./src/parser/handle_files.c\
./src/parser/in_out_file_loper.c\
./src/parser/input_preperations.c\
./src/parser/input_work.c\
./src/parser/quote_and_link_toaray.c\
./src/parser/syntax_checks.c\
./src/utils/environment.c\
./src/utils/here_doc.c\
./src/utils/mi_get_next_line.c\
./src/utils/plus_split.c\
./src/utils/slash_join.c\

SRCWIN = $(SRC_DIR)*.c ./src/linked_lists/*.c ./src/builtins/*.c ./libs/libft/*.c

OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o, $(SRC))

HEADERS := $(HEADER_DIR)*.h
LIBFT_DIR := /libft/
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
	@rm -f ./libft/libft.a
	@echo "\n$(RED)all deleted!$(DEFAULT)"

re: fclean all

no: 
	@$(CC) -o $(NAME) $(SRC) $(LFR) $(LFRC) -L ./libft -lft
win: 
	@$(CC) -o $(NAME) $(SRCWIN) -L/usr/include -lreadline -ltinfo

.PHONY: all clean fclean re
