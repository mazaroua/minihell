NAME = minishell
CC = cc 
FLAGS = -g #-Wall #-Werror #-Wextra 
SRC = minishell.c utils.c utils2.c tokenizer.c tokenizer_utils.c syntax.c parser.c parser_utils.c expander.c
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