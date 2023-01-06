# Note, for the minilibx to be findable, one either needs to have the lib in the same folder as the exec, or add the lib
# to the path like this: `export DYLD_LIBRARY_PATH=/Users/jwikiera/Projets/fdf/FDF/minilibx_mms_20191025_beta:$DYLD_LIBRARY_PATH`

NAME					:= fdf

UNAME_S					:= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  FSANITIZE				:= -fsanitize=address -fsanitize=leak
  FRAMEWORK				:=
  LINUX_LIBS			:= -lXext -lX11
  LINUX_INCLUDES		:= -I/usr/include
  OS_FLAG				:= -D LINUX
else
  FSANITIZE				:=
  FRAMEWORK				:= -framework OpenGL -framework AppKit
  LINUX_LIBS			:=
  LINUX_INCLUDES		:=
  OS_FLAG				:= -D OSX
endif

CC						:= cc
CFLAGS					:= -Wall -Wextra -Werror -O3 -fno-omit-frame-pointer -ggdb -O0 -fstack-protector-all $(FSANITIZE) $(OS_FLAG)
RM						:= rm -f

LIB_DIRECTORY			:= ./libs/

LIBFT					:= $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY			:= $(LIB_DIRECTORY)libft/
LIBFT_HEADERS			:= $(LIBFT_DIRECTORY)includes/

LIBPRINTF				:= $(LIBPRINTF_DIRECTORY)libftprintf.a
LIBPRINTF_DIRECTORY		:= $(LIB_DIRECTORY)libprintf/
LIBPRINTF_HEADERS		:= $(LIBPRINTF_DIRECTORY)includes/

ifeq ($(UNAME_S),Darwin)
  MINILIBX_DIRECTORY	:= $(LIB_DIRECTORY)minilibx_mms_20191025_beta
  MINILIBX_NAME			:= libmlx.dylib
else
  MINILIBX_DIRECTORY	:= $(LIB_DIRECTORY)minilibx-linux
  MINILIBX_NAME			:= libmlx.a
endif

MINILIBX				:= $(MINILIBX_DIRECTORY)/$(MINILIBX_NAME)
MINILIBX_HEADERS		:= $(MINILIBX_DIRECTORY)

INCLUDE_DIR				:= ./includes/

# lm: default math lib
LIBRARIES				:= -lmlx -lm -lftprintf -lft -L. -L$(LIBFT_DIRECTORY) -L$(LIBPRINTF_DIRECTORY) -L$(MINILIBX_DIRECTORY) $(FRAMEWORK) $(LINUX_LIBS)
INCLUDES				:= -I$(LIBFT_HEADERS) -I$(LIBPRINTF_HEADERS) -I$(MINILIBX_HEADERS) -I$(INCLUDE_DIR) $(LINUX_INCLUDES)

SOURCES_DIRECTORY		:= ./sources/
SOURCES_LIST			:= main.c\
							color.c\
							parsing.c\
							parsing2.c\
							drawing.c\
							mlx_helpers.c\
							draw_line.c\
							circle_bresenham.c\
							vect.c\
							draw_cube.c\
							print_util.c\
							set_screen_info.c\
							screen_plane.c\
							keyhandler.c\
							drawing_map.c\
							init.c\
							arg_handler.c\
							get_proj_map.c
SOURCES					:= $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))
HEADER_LIST				:= fdf.h
HEADER_FILES			:= $(addprefix $(INCLUDE_DIR), $(HEADER_LIST))

OBJECTS_DIRECTORY		:= objects/
OBJECTS_LIST			:= $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS					:= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

.PHONY: all clean fclean re docker_build docker_run docker_clean

all: $(NAME)

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

$(NAME): $(LIBFT) $(LIBPRINTF) $(MINILIBX) $(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER_FILES)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

clean:
	@$(MAKE) -sC $(LIBPRINTF_DIRECTORY) clean
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@$(MAKE) -sC $(MINILIBX_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@rm -rf *.dSYM
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

norm:
	norminette includes/ sources/ libs/libft/ libs/libprintf/

funcs: $(NAME)
	nm -u $(NAME)