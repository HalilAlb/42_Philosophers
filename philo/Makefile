NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
		pars.c \
		init.c \
		safe_func.c \
		utils.c \
		dinner.c \
		geters_seters.c \
		hero_utils.c \
		write.c \
		monitor.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

leak: $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -o $(NAME)

debug: 
	$(CC) $(CFLAGS) -fsanitize=address -g $(SRCS) -o $(NAME)

tsan: $(SRCS)
	$(CC) $(CFLAGS) -fsanitize=thread $(SRCS) -o $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re leak debug