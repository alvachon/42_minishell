NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = minishell.c echo.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

LIBDIR = lib/libft/

LIBFT = lib/libft/libft.a

all : $(NAME) $(SRC)

$(NAME) : $(OBJ)
	$(MAKE) -C $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean : 
	$(RM) $(OBJ)
	$(RM) $(LIBDIR)*.o

fclean : clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re : fclean all

.PHONY : all clean fclean re
