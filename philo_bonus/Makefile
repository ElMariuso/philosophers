# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 17:55:55 by mthiry            #+#    #+#              #
#    Updated: 2022/06/15 19:18:10 by mthiry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =  main.c \
		init_all.c \
		utils.c \
		processus.c \
		processus_utils.c \
		eating.c \
		exit.c \
		error.c \
		main_routines.c \

all: $(NAME)

.PHONY: all clean fclean re

OBJS = $(SRCS:%.c=%.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $? -o $(?:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
