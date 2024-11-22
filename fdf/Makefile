NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx #-fsanitize=address -g3
INCLUDE = .

SRC =  main.c\
	   ft_draw.c\
	   ft_handle_event.c\
	   ft_parse_map.c\
	   ft_math.c\
	   ft_cube.c\
	   ft_color.c\
	   ft_point.c\
	   ft_image.c\
	   ft_setting.c\
	   ft_utils.c


LIBFTDIR = ./libft

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC) fdf.h
	$(CC) $(CFLAGS) -Imlx -Lmlx -lmlx -framework OpenGL -framework Appkit -o $(NAME) $(SRC) $(LIBFT)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	make -C $(LIBFTDIR) clean

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
