NAME = philo

SRCS = libftFunctions.c philosophersState.c

MAIN = Philosophers.c

HEADER = philosophers.h 

# OBJ = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) :  $(HEADER) #$(OBJ)
	cc -Wall -Wextra -Werror $(SRCS) $(MAIN) -o $(NAME)

clean :
	#rm -rfv $(OBJ) 

fclean : #clean
	rm -rfv $(NAME)

re : fclean all