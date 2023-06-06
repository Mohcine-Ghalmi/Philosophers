# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/31 21:02:49 by mghalmi           #+#    #+#              #
#    Updated: 2023/06/06 17:19:50 by mghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = libftFunctions.c philosophersState.c Philosophers.c utils.c

HEADER = philosophers.h 

OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) $(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) -o $(NAME) #-fsanitize=thread

clean :
	rm -rfv $(OBJ) 

fclean : clean
	rm -rfv $(NAME)

re : fclean all