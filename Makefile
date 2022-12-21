# Note, for the minilibx to be findable, one either needs to have the lib in the same folder as the exec, or add the lib
# to the path like this: `export DYLD_LIBRARY_PATH=/Users/jwikiera/Projets/fdf/FDF/minilibx_mms_20191025_beta:$DYLD_LIBRARY_PATH`

NAME				:= fdf

CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror -O3 -fno-omit-frame-pointer -g -O0 -fstack-protector-all
RM					:= rm -f

LIB_DIRECTORY		:= ./libs/

LIBFT				:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY		:= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS		:= $(LIBFT_DIRECTORY)includes/

LIBPRINTF			:= $(LIBPRINTF_DIRECTORY)libftprintf.a
LIBPRINTF_DIRECTORY	:= $(LIB_DIRECTORY)libprintf/
LIBPRINTF_HEADERS	:= $(LIBPRINTF_DIRECTORY)includes/

MINILIBX_DIRECTORY	:= $(LIB_DIRECTORY)minilibx_mms_20191025_beta
MINILIBX_NAME		:= libmlx.dylib
MINILIBX			:= $(MINILIBX_DIRECTORY)/$(MINILIBX_NAME)
MINILIBX_HEADERS	:= $(MINILIBX_DIRECTORY)

INCLUDE_DIR			:= ./includes/

# lm: default math lib
LIBRARIES			:= -lmlx -lm -lft -lftprintf -L$(LIBFT_DIRECTORY) -L$(LIBPRINTF_DIRECTORY) -L$(MINILIBX_DIRECTORY) -framework OpenGL -framework AppKit
INCLUDES			:= -I$(LIBFT_HEADERS) -I$(LIBPRINTF_HEADERS) -I$(MINILIBX_HEADERS) -I$(INCLUDE_DIR)

SOURCES_DIRECTORY	:= ./sources/
SOURCES_LIST		:= main.c\
						color.c\
						parsing.c
SOURCES				:= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

OBJECTS_DIRECTORY	:= objects/
OBJECTS_LIST		:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS				:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

ifeq ("$(uname -r)", "5.10.104-linuxkit")
  LBSD				:= -lbsd
  FSANITIZE			:= -fsanitize=address -fsanitize=leak
else
  LBSD				:=
  FSANITIZE			:=
endif

.PHONY: all clean fclean re docker_build docker_run docker_clean

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	#@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
	#@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): Creating $(LIBFT)..."
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

$(LIBPRINTF):
	@echo "$(NAME): Creating $(LIBPRINTF)..."
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY)

$(MINILIBX):
	@echo "$(NAME): Creating $(MINILIBX)..."
	# For some reason -sC doesn't play nicely with clion for the minilibx
	#$(MAKE) -sC $(MINILIBX_DIRECTORY)
	cd $(MINILIBX_DIRECTORY) && $(MAKE)
	cp $(MINILIBX) .

all: $(NAME)

$(NAME): $(LIBFT) $(LIBPRINTF) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBRARIES) $(INCLUDES) $(OBJECTS) -o $(NAME)

clean:
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	@rm -f $(MINILIBX)
	@echo "$(NAME): $(MINILIBX) was deleted"
	@rm -f $(NAME)
	@echo "$(NAME): $(NAME) was deleted"
	@rm -f $(MINILIBX_NAME)
    @echo "$(NAME): $(MINILIBX_NAME) was deleted"

docker_build:
	docker build -t fdf .

docker_run:
	docker run -it fdf

docker_clean:
	docker system prune -a --volumes

re: fclean all
