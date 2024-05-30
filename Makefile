NAME = fractol

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux -g
LDFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS = fractol.c utils.c init.c events.c math.c render.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx-linux

MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all