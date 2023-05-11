NAME = philo

SRCS = test.c libftFunctions.c philosophersState.c

HEADER = philosophers.h 

# OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) #$(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) -o $(NAME)

clean :
	#rm -rfv $(OBJ) 

fclean : #clean
	rm -rfv $(NAME)

re : fclean all