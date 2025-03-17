NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address -g3
INCLUDE = .

SRC =  main.c               \
	   vars.c            \
	   handle_event.c    \
	   draw.c            \
	   draw_utils.c      \
	   text_field.c      \
	   text_field_draw.c \
	   color_picker.c    \
	   color_option.c    \
	   color_utils.c     \
	   color.c           \
	   mouse.c           \
	   label.c           \
	   map.c             \
	   parse_map.c       \
	   math.c            \
	   cube.c            \
	   point.c           \
	   image.c           \
	   camera.c          \
	   camera_utils.c    \
	   rectangle.c       \
	   circle.c          \
	   utils.c

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
