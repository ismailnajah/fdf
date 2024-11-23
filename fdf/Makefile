NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address -g3
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

OBJ := $(SRC:.c=.o)

LIBFTDIR = ./libft

LIBFT = $(LIBFTDIR)/libft.a

OS := $(shell uname)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) fdf.h
ifeq ($(OS),Linux)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)
else
	$(CC) $(CFLAGS) $(OBJ) -Imlx_mac -Lmlx -lmlx -framework OpenGL -framework Appkit -o $(NAME) $(LIBFT)
endif

%.o : %.c fdf.h
ifeq ($(OS), Linux)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
else
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
endif

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	make -C $(LIBFTDIR) clean
	@rm -rf $(OBJ)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
