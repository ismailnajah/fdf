NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address -g3
INCLUDE = .

SRC =  main.c               \
	   ft_vars.c            \
	   ft_handle_event.c    \
	   ft_draw.c            \
	   ft_draw_utils.c      \
	   ft_text_field.c      \
	   ft_text_field_draw.c \
	   ft_color_picker.c    \
	   ft_color_option.c    \
	   ft_color_utils.c     \
	   ft_color.c           \
	   ft_mouse.c           \
	   ft_label.c           \
	   ft_map.c             \
	   ft_parse_map.c       \
	   ft_math.c            \
	   ft_cube.c            \
	   ft_point.c           \
	   ft_image.c           \
	   ft_camera.c          \
	   ft_camera_utils.c    \
	   ft_rectangle.c       \
	   ft_circle.c          \
	   ft_utils.c

OBJDIR := obj
OBJ := $(SRC:.c=.o)
OBJ := $(OBJ:%=$(OBJDIR)/%)

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c fdf.h | $(OBJDIR)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT):
	make -s -C $(LIBFTDIR)

clean:
	make -s -C $(LIBFTDIR) clean
	rm -rf $(OBJDIR)

fclean: clean
	make -s -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
