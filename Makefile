# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 21:02:49 by mghalmi           #+#    #+#              #
#    Updated: 2023/06/05 21:23:24 by mghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = libftFunctions.c philosophersState.c Philosophers.c

HEADER = philosophers.h 

OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) $(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) -o $(NAME)

clean :
	rm -rfv $(OBJ) 

fclean : clean
	rm -rfv $(NAME)

re : fclean all