SRCS =	philo.c utils.c
OBJS = ${SRCS:.c=.o}
NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 

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
