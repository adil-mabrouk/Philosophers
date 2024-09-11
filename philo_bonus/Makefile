# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amabrouk <amabrouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 14:45:46 by amabrouk          #+#    #+#              #
#    Updated: 2024/09/09 19:58:45 by amabrouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror # -fsanitize=thread -g

SRC = philo_bonus.c parsing_bonus.c utils_bonus.c routine_bonus.c monitor_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJ) philo_bonus.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

