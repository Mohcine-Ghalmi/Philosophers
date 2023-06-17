# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/16 13:06:15 by mghalmi           #+#    #+#              #
#    Updated: 2023/06/17 09:20:07 by mghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =  checkDeath.c philosophers.c  creatPhilosophers.c helper.c  startProcess.c

HEADER = philo_bonus.h

OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) $(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) -o $(NAME) #-fsanitize=thread 

clean :
	rm -rfv $(OBJ) 

fclean : clean
	rm -rfv $(NAME)

re : fclean all