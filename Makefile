NAME = pipex
LIBNAME = libpipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

files = pipex redirection handle_cmd
CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBNAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re