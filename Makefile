NAME := philo
CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -pthread
HEADER := -I./includes
P_SRCSDIR := ./srcs
P_SRCS := main.c\
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

OBJS_DIR := ./obj
#OBJS = ${addprefix ${OBJS_DIR), ${P_SRCS:.c=.o}}
OBJS := $(addprefix $(OBJS_DIR)/, $(notdir $(P_SRCS:.c=.o)))
DEPS := $(OBJS:.o=.d)
# -g -fsanitize=address -g -fsanitize=thread
RM := rm -rf

$(NAME): $(OBJS)
	$(CC) -o $@ $^

$(OBJS_DIR)/%.o: $(P_SRCSDIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

all: $(NAME)

clean:
	rm -f $(NAME) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)