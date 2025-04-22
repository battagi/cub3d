CC = cc
CFLAG = -fsanitize=address -g

RM = rm -rf  
HEADERS = ./includes/cube3d.h ./includes/get_next_line.h ./includes/libft.h
SRCS =	./srcs/mandatory/main.c \
		./srcs/mandatory/parsing/parsing.c \
		./srcs/mandatory/parsing/parse_txts.c \
		./srcs/mandatory/parsing/parsing_utils.c \
		./srcs/mandatory/parsing/parsing_utils2.c \
		./srcs/mandatory/parsing/map_utils.c \
		./srcs/mandatory/parsing/map_utils2.c \
		./srcs/mandatory/parsing/map_utils3.c \
		./srcs/mandatory/raycasting/dist_calcul.c \
		./srcs/mandatory/raycasting/rc_utils.c \
		./srcs/mandatory/raycasting/raycast.c \
		./srcs/mandatory/rendering/render_walls.c \
		./srcs/mandatory/rendering/render_utils.c \
		./srcs/tests.c \
		./srcs/draw_map.c \
		./srcs/player.c

SRCS_B =	./srcs/bonus/main_bonus.c \
			./srcs/bonus/parsing/parsing.c \
			./srcs/bonus/parsing/parse_txts.c \
			./srcs/bonus/parsing/parsing_utils.c \
			./srcs/bonus/parsing/parsing_utils2.c \
			./srcs/bonus/parsing/parsing_utils3.c \
			./srcs/bonus/parsing/map_utils.c \
			./srcs/bonus/parsing/map_utils2.c \
			./srcs/bonus/parsing/map_utils3.c \
			./srcs/bonus/raycasting/dist_calcul.c \
			./srcs/bonus/raycasting/rc_utils.c \
			./srcs/bonus/raycasting/raycast.c \
			./srcs/mandatory/rendering/render_walls.c \
			./srcs/mandatory/rendering/render_utils.c \
			./srcs/bonus/rendering/render_sprites.c \
			./srcs/bonus/rendering/sprite_utils.c \
			./srcs/tests.c \
			./srcs/bonus/rendering/mini_map.c \
			./srcs/bonus/parsing/door.c \
			./srcs/bonus/raycasting/vdist_door.c \
			./srcs/bonus/raycasting/hdist_door.c 

INCLUDES = MLX/build/libmlx42.a MLX/build/libglfw3.a -Iinclude -lm -framework Cocoa -framework OpenGL -framework IOKit

NAME = cube
NAME_B = cube_b
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)
LIBFT=libft/libftprintf.a



all : $(NAME)

bonus: $(NAME_B)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) -O3 $(CFLAG) $(LIBFT) $(INCLUDES) $(OBJS) -o $(NAME)

$(NAME_B) : $(LIBFT) $(OBJS_B)
	$(CC) -g $(CFLAG) $(LIBFT) $(INCLUDES) $(OBJS_B) -o $(NAME_B)

$(LIBFT):
	make -C libft/

clean:
	@$(RM) $(OBJS) $(OBJS_B)
	@make clean -C libft

%.o : %.c
	$(CC) -c $^ -o $@ 

fclean : clean 
		@$(RM) $(NAME) $(NAME_B) 
		@make fclean -C libft

re : fclean all 

.PHONY: all clean fclean re 