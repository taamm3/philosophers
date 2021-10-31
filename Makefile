NAME = philo
SRC = main.c\
		utils.c\

OBJS = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra
CC = gcc
RM = rm -rf

${NAME}: ${OBJS}
		${CC} ${FLAGS} ${OBJS} -o ${NAME} 

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

#clang -lpthread