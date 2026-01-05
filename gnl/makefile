# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror

# Executable Name
NAME = gnl.a

# Source Files (all .c files in the current directory)
FILES = get_next_line.c get_next_line_utils.c

# Object Files
OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
