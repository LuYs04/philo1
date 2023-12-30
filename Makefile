# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tumolabs <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/30 16:52:57 by tumolabs          #+#    #+#              #
#    Updated: 2023/12/30 16:53:01 by tumolabs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC =	philo.c			\
		philo_utils.c	\
		data_init.c		\
		philo_act.c		\
		philo_die.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean :
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all

.PHONY: re, all, fclean, clean
