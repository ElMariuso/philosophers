# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mthiry <mthiry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 18:09:46 by mthiry            #+#    #+#              #
#    Updated: 2022/06/17 15:46:11 by mthiry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS =  main.c \
		init_all.c \
		utils.c \
		processus.c \
		processus_utils.c \
		eating.c \
		exit.c \
		
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