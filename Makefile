# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ego <ego@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 15:01:20 by ego               #+#    #+#              #
#    Updated: 2025/07/03 19:49:52 by ego              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SDIR		=	srcs/
IDIR		=	includes/
LDIR		=	lib/
ODIR		=	objs/

SRC			=	main.c
SRC			+=	debug/lights.c			\
				debug/objects.c			\
				debug/parsing.c			\
				debug/scene.c
SRC			+=	parsing/argument.c		\
				parsing/bump.c			\
				parsing/color.c			\
				parsing/convert.c		\
				parsing/coordinates.c	\
				parsing/error.c			\
				parsing/identifier.c	\
				parsing/light.c			\
				parsing/lists.c			\
				parsing/object.c		\
				parsing/scale.c			\
				parsing/scene.c			\
				parsing/texture.c		\
				parsing/utils.c
SRC			+=	raycasting/color.c				\
				raycasting/cone_intersec.c		\
				raycasting/cylinder_intersec.c	\
				raycasting/cylinder_uv.c		\
				raycasting/intersections.c 		\
				raycasting/is_shadowed.c		\
				raycasting/normal.c				\
				raycasting/plane_intersec.c		\
				raycasting/shaders.c			\
				raycasting/sphere_intersec.c	\
				raycasting/texture.c			\
				raycasting/uv.c
SRC			+=	utils/display.c			\
				utils/free.c			\
				utils/string.c
SRC			+=	graphix/display.c		\
				graphix/mlx_utils.c		\
				graphix/view_utils.c 	\
				graphix/render.c

OBJS		=	$(addprefix $(ODIR), $(SRC:.c=.o))
SRCS		=	$(addprefix $(SDIR), $(SRC))

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
IFLAGS		=	-I $(IDIR)
RM			=	rm -rf

OS := $(shell uname)
ifeq ($(OS), Darwin)
	LFLAGS	=	-L $(LDIR)libft -lft -L $(LDIR)mlx -lmlx -framework OpenGL -framework AppKit
else ifeq ($(OS), Linux)
	LFLAGS	=	-L $(LDIR)libft -lft -L $(LDIR)mlx -lmlx -lXext -lX11 -lm
endif

LIBFT		=	$(LDIR)libft/libft.a
LIBX		=	$(LDIR)mlx/libmlx.a
NAME		=	miniRT

all			:	$(NAME)

bonus		:	$(NAME)

$(NAME)		:	$(LIBFT) $(LIBX) $(ODIR) $(OBJS)
				$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)
				make -s header
				printf "$(COLOR_G)[OK] miniRT is ready!$(C_RESET)\n" || \
				printf "$(COLOR_R)[KO] Something went wrong.$(C_RESET)\n"

$(LIBFT)	:
				printf "$(COLOR_B)Building libft...$(C_RESET)\n"
				make -sC $(LDIR)libft
				printf "$(COLOR_G)[OK] libft is ready!$(C_RESET)\n" || \
				(printf "$(COLOR_R)[KO] Failed to build libft.$(C_RESET)\n" && false)

$(LIBX)		:
				printf "$(COLOR_B)Building mlx...$(C_RESET)\n"
				make -sC $(LDIR)mlx
				printf "$(COLOR_G)[OK] mlx is ready!$(C_RESET)\n" || \
				(printf "$(COLOR_R)[KO] Failed to build mlx.$(C_RESET)\n" && false)

$(ODIR)		:
				mkdir -p $(ODIR)
				mkdir -p $(ODIR)debug
				mkdir -p $(ODIR)parsing
				mkdir -p $(ODIR)utils
				mkdir -p $(ODIR)raycasting
				mkdir -p $(ODIR)graphix
				mkdir -p $(ODIR)tests
				printf "Object directory created.\n"

$(ODIR)%.o	:	$(SDIR)%.c
				echo "Compiling $<..."
				$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ || \
				(printf "$(COLOR_R)[KO] Compilation failed.$(C_RESET)\n" && false)

clean		:
				echo "Removing object files..."
				make -sC $(LDIR)libft clean
				make -sC $(LDIR)mlx clean
				$(RM) $(ODIR)
				printf "$(COLOR_O)[OK] All object files have been removed.$(C_RESET)\n"

fclean		:
				echo "Removing object and binary files..."
				make -sC $(LDIR)libft fclean
				make -sC $(LDIR)mlx clean
				$(RM) $(ODIR)
				$(RM) $(NAME)
				printf "$(COLOR_O)[OK] All binary files have been removed.$(C_RESET)\n"

re			:	fclean all

norm		:
				norminette -R CheckForbiddenSourceHeader $(SDIR) $(IDIR) $(LDIR)libft

.PHONY		:	all clean fclean re
.SILENT		:	all bonus $(NAME) $(LIBFT) $(LIBX) $(ODIR) $(OBJS) clean fclean re norm header

COLOR_R		= \033[31m
COLOR_O		= \033[38;5;214m
COLOR_Y		= \033[33m
COLOR_G		= \033[32m
COLOR_B		= \033[34m
COLOR_V		= \033[38;5;93m
COLOR_I		= \033[3m
C_RESET		= \033[0m

header	:
			printf "========================================\n"
			printf "$(COLOR_O)           __         __ ______ _______ $(C_RESET)\n"
			printf "$(COLOR_R).--------.|__|.-----.|__|   __ \_     _|$(C_RESET)\n"
			printf "$(COLOR_G)|        ||  ||     ||  |      < |   |  $(C_RESET)\n"
			printf "$(COLOR_B)|__|__|__||__||__|__||__|___|__| |___|  $(C_RESET)\n"
			printf "$(COLOR_I)$(COLOR_V)          by hcavet & vviterbo$(C_RESET)\n"
			printf "========================================\n"
