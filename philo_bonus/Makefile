# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 16:46:24 by mghalmi           #+#    #+#              #
#    Updated: 2023/06/15 16:46:39 by mghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = 

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