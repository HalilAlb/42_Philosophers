CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo

SRCS = main.c \
		pars.c \
		init.c \
		safe_func.c \
		utils.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re
