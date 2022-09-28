CC = gcc
CFLAGS = -Werror -Wextra -Wall -g

NAME=philo

SRC = life_of_philo.c philo.c philo_utlit.c ft_atoi.c parsing.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o philo $(OBJ) -pthread -o $(NAME)

re: fclean all

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

.PHONY: all clean fclean