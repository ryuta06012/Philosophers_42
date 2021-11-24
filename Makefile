NAME = philo

HEADER = philosopher.h

P_SRCS = main.c \
	ft_atoi.c \
	set_up.c \
	eat.c \
	exit.c \
	get_fork.c \
	put_forks.c \
	put_message.c \
	think_and_sleep.c \
	utils.c \


OBJS = ${P_SRCS:.c=.o}

CC = gcc

# -g -fsanitize=address -g -fsanitize=thread

CFLAGS = -Wall -Wextra -Werror

PFLAGS = -pthread

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS} ${HEADER}
	${CC} ${CFLAGS} ${PFLAGS} -o ${NAME} ${P_SRCS} -I ${HEADER}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re