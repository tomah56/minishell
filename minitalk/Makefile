CC = gcc
NAMEC = client
NAMES = server
FLAGS = -Wall -Wextra -Werror
SRCC = 	client.c long_atoi.c
SRCS = 	server.c simple_printf.c

all: $(NAMEC) $(NAMES)

$(NAMEC): $(SRCC)
	$(CC) -o $(NAMEC) $(FLAGS) $(SRCC)

$(NAMES): $(SRCS)
	$(CC) -o $(NAMES) $(FLAGS) $(SRCS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAMEC) $(NAMES)

re: fclean all
