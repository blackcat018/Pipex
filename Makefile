NAME = pipex
LIBNAME = libpipex.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

files = pipex redirection handle_cmd is_cmd_a_path
CFILES = $(files:%=%.c)
OBJS = $(files:%=%.o)

bonus_files = Bonus/pipex_bonus Bonus/redirection_bonus \
              Bonus/handle_cmd_bonus Bonus/is_cmd_a_path_bonus \
              Bonus/get_next_line/get_next_line_bonus \
              Bonus/get_next_line/get_next_line_utils_bonus \
			  Bonus/here_doc_bonus

BONUS_CFILES = $(bonus_files:%=%.c)

BONUS_OBJS = $(bonus_files:%=%.o)

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)

bonus: $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) $(LIBFT)

$(LIBNAME): $(OBJS)
	ar crs $@ $(OBJS)

%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

Bonus/%.o: Bonus/%.c Bonus/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

Bonus/get_next_line/%.o: Bonus/get_next_line/%.c Bonus/get_next_line/get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBNAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re