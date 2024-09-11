# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 14:45:46 by amabrouk          #+#    #+#              #
#    Updated: 2024/09/10 14:29:58 by amabrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g

SRC = philo.c parsing.c utils.c routine.c monitor.c

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

