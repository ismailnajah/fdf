NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -lm

INCLUDE = .

SRC =  main.c\

LIBFTDIR = ./libft

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(NAME) $(SRC) $(LIBFT)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	make -C $(LIBFTDIR) clean

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
