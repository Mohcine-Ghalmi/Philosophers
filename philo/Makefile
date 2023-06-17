# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/15 12:30:03 by mghalmi           #+#    #+#              #
#    Updated: 2023/06/17 09:17:33 by mghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = create_threads.c giving_forks.c   helper.c   philosophers.c utils.c

HEADER = philosophers.h 

OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) $(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) -o $(NAME)  #-fsanitize=thread 

clean :
	rm -rfv $(OBJ) 

fclean : clean
	rm -rfv $(NAME)

re : fclean all