# Mandatory functions
NAME = fract-ol
SRC = ./src/
SRCS = $(wildcard $(SRC)*.c)
OBJS = $(SRCS:.c=.o)
HEADER = ./include/fract-ol.h
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./include
RM = rm -f
MLX = ./minilibx

# Plataforma
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_FLAGS = -lXext -lX11 -lm
else
	MLX_FLAGS = -framework OpenGL -framework AppKit
endif

# Color
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RESET   = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compilando MiniLibX...$(RESET)"
	make -C $(MLX)
	@echo "$(GREEN)Compilando fract-ol...$(RESET)"
	$(CC) $(OBJS) $(MLX)/libmlx.a -o $(NAME) $(MLX_FLAGS)
	@echo "$(BLUE)"
	@echo "$(YELLOW)           ($(RESET)__$(YELLOW))\           $(RESET)"
	@echo "$(YELLOW)           ($(RESET)oo$(YELLOW))\\________  $(RESET)"
	@echo "$(RESET)           /|| \\        \\ fract-ol READY$(RESET)"
	@echo "$(RESET)              ||------w | $(RESET)"
	@echo "$(RESET)              ||       || $(RESET)"
	@echo "$(YELLOW)THE COW MAKES MUUUUUUUUUU!$(RESET)"
	@echo "$(RESET)"

%.o: %.c $(HEADER)
	@echo "$(BLUE)Compilando: $<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(GREEN)Eliminando objetos...$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(GREEN)Eliminando todo...$(RESET)"
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
