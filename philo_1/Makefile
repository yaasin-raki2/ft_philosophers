NAME = philosophers

SRCS = $(wildcard srcs/*c) $(wildcard utils/*c)

FLAGS = -Wall -Wextra -Werror

LIBS = -lpthread

INCS = ./incs

all: $(NAME)

$(NAME): $(SRCS)
	@gcc ${FLAGS} $(SRCS) -o ${NAME} ${LIBS} -I ${INCS}

clean:
	@rm -f $(NAME)
				
fclean:	clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re