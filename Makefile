NAME = minishell
CC = cc 
FLAGS = -g #-Wall #-Werror #-Wextra 
SRC = minishell.c utils.c utils2.c tokenizer.c tokenizer_utils.c tokenizer_utils2.c syntax.c parser.c parser_utils.c expander.c  cd.c echo.c excuter.c pipes.c excution.c init_env.c
OBJ = $(SRC:.c=.o)


all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o

fclean:clean
	rm -rf $(NAME)

re:fclean all

.PHONY: all fclean clean   