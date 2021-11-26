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
	validate.c

OBJS_DIR = obj/
#OBJS = ${addprefix ${OBJS_DIR}, ${P_SRCS:.c=.o}}
OBJS = ${P_SRCS:.c=.o}
DEPS = ${OBJS:.o=.d}
CC = gcc
# -g -fsanitize=address -g -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

all: ${NAME}

-include ${DEPS}

${NAME}: ${OBJS} ${OBJS_DIR}
	${CC} ${CFLAGS} -o $@ ${OBJS}

${OBJS_DIR}%.o: ${P_SRCS}
	${CC} ${CFLAGS} -I ${HEADER} -o $@ -c $<

${OBJS_DIR}:
	@-mkdir $@
clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re