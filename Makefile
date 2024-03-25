SRCS =	philo.c utils.c
PRINTF = ft_printf/libftprintf.a
OBJS = ${SRCS:.c=.o}
NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 

$(NAME): print_f $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

print_f:
	@cd ft_printf && make

all: ${NAME}

%.o:	%.c philo.h ft_printf/ft_printf.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	@${RM} ${OBJS}
	@cd ft_printf && make clean

fclean: clean
	@${RM} ${NAME}
	@cd ft_printf && make fclean

re: fclean all

.PHONY : all clean fclean re
