SRCS =	philo.c utils_philo.c routine.c helpers.c init_philos.c
OBJS = ${SRCS:.c=.o}
NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=thread

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  

all: ${NAME}

%.o:%.c philo.h 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
