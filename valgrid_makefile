CC = gcc
NAME = minishellll
FLAGS = -Wall -Wextra -Werror
SUB_LIB = libft/libft.a
PATHLIB = libft/
# SRCWIN = *.c ./src/linked_lists/*.c ./src/builtins/*.c ./libs/libft/*.c
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

# OBJ = $(SRC:.c=.o)
LFJ = -L$$HOME/.brew/opt/readline/lib -lreadline
CPY = -I$$HOME/.brew/opt/readline/include
GREEN := \033[0;32m
YELLOW := \033[1;33m
RED := \033[1;31m
DEFAULT := \033[0m

all: $(NAME)

$(SUB_LIB): $(PATHLIB)/*.c
	@make -C $(PATHLIB)

$(NAME): $(SUB_LIB) $(SRC) ./include/minishell.h
	@$(CC) -o $(NAME) $(SRC) $(LFJ) $(CPY) -I $(PATHLIB) -L ./libft -lft
	@echo "\n$(GREEN)$(NAME) created$(DEFAULT)"
# @$(CC) -o $(NAME) $(FLAGS) $(SRC) $(LFJ) $(CPY) -I $(PATHLIB) -L ./libft -lft

cleanlib:
	@make -C $(PATHLIB) clean

clean: cleanlib
	@rm -f *.o
	@rm -f ./*/*.o
	@rm -f ./*/*/*.o
	@echo "\n$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(PATHLIB) fclean
	@echo "\n$(RED)all deleted!$(DEFAULT)"

re: fclean all

no: 
	@$(CC) -o $(NAME) $(SRC) $(LFJ) $(CPY) -L ./libs -lft
# win: 
# @$(CC) -o $(NAME) $(SRCWIN) -L/usr/include -lreadline -ltinfo