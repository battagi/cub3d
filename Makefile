CC = cc
CFLAGS = #-g -fsanitize=address

RM = rm -rf  
HEADERS = ./includes/cube3d.h ./includes/get_next_line.h ./includes/libft.h
SRCS = ./srcs/main.c ./srcs/parsing.c ./srcs/parsing_utils.c ./srcs/parsing_utils2.c ./srcs/map.c ./srcs/tests.c ./srcs/draw_map.c ./srcs/player.c

INCLUDES = MLX/build/libmlx42.a MLX/build/libglfw3.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit

NAME = cube
OBJS = $(SRCS:.c=.o)
LIBFT=libft/libftprintf.a



all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(INCLUDES) $(OBJS) -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	@$(RM) $(OBJS) 
	@make clean -C libft

%.o : %.c $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@ 

fclean : clean 
		@$(RM) $(NAME) 
		@make fclean -C libft

re : fclean all 

.PHONY: all clean fclean re 