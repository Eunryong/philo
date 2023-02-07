# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 19:00:57 by eunrlee           #+#    #+#              #
#    Updated: 2023/02/08 00:04:57 by eunrlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra# -fsanitize=thread
NAME = philo
SRCS = philo.c utils.c init.c thread.c share.c
OBJS = $(SRCS:.c=.o)

all : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ 
clean :
	rm -f $(OBJS) $(B_OBJS)
fclean : clean
	rm -f $(NAME)
re : 
	make fclean
	make all
.PHONY: re fclean clean
