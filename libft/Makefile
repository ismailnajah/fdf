NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =  ft_memmove.c\
	 ft_memset.c\
	 ft_bzero.c\
	 ft_itoa.c\
	 ft_substr.c\
	 ft_strjoin.c\
	 ft_strnstr.c\
	 ft_isprint.c\
	 ft_memcpy.c\
	 ft_strncmp.c\
	 ft_isdigit.c\
	 ft_memcmp.c\
	 ft_strrchr.c\
	 ft_atoi.c\
	 ft_strtrim.c\
	 ft_isascii.c\
	 ft_isalpha.c\
	 ft_isalnum.c\
	 ft_memchr.c\
	 ft_strlcpy.c\
	 ft_strchr.c\
	 ft_tolower.c\
	 ft_toupper.c\
	 ft_strmapi.c\
	 ft_striteri.c\
	 ft_putchar_fd.c\
	 ft_putstr_fd.c\
	 ft_putendl_fd.c\
	 ft_putnbr_fd.c\
	 ft_putchar.c\
	 ft_putstr.c\
	 ft_calloc.c\
	 ft_split.c\
	 ft_strlcat.c\
	 ft_strlen.c\
	 ft_strdup.c\
	 ft_error.c\
	 get_next_line.c

BSRC = ft_lstnew_bonus.c\
	   ft_lstadd_front_bonus.c\
	   ft_lstsize_bonus.c\
	   ft_lstlast_bonus.c\
	   ft_lstadd_back_bonus.c\
	   ft_lstdelone_bonus.c\
	   ft_lstclear_bonus.c\
	   ft_lstiter_bonus.c\
	   ft_lstmap_bonus.c

SDIR = .
OBJ := $(SRC:.c=.o)

BOBJ := $(BSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rsc $(NAME) $(OBJ)

bonus: $(NAME) $(BOBJ)
	ar rsc $(NAME) $(BOBJ)

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
.SECONDARY: $(OBJ) $(BOBJ)
