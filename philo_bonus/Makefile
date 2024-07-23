SRCS =	philo_bonus.c check_errors_bonus.c routine_bonus.c helpers_bonus.c check_death.c
OBJS = ${SRCS:.c=.o}
NAME = philo_bonus
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  

all: ${NAME}

%.o:%.c philo_bonus.h 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
