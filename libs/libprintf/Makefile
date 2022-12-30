NAME		:= libftprintf.a
#SRCS		:= ft_printf.c conversion_helpers.c flag_helpers.c ft_t_format_builder.c precision_helpers.c print_char.c util.c width_helpers.c print_str.c math_util.c math_util2.c util2.c print_void_ptr.c put_hex_fd.c print_int.c util3.c print_unsigned.c put_size_t_fd.c print_hexadecimal.c
SRCS		= libft/ft_atoi.c                 libft/ft_isascii.c              libft/ft_lstadd_front_bonus.c   libft/ft_lstmap_bonus.c         libft/ft_memcpy.c               libft/ft_putnbr_fd.c            libft/ft_striteri.c             libft/ft_strmapi.c              libft/ft_substr.c \
              libft/ft_bzero.c                libft/ft_isdigit.c              libft/ft_lstclear_bonus.c       libft/ft_lstnew_bonus.c         libft/ft_memmove.c              libft/ft_putstr_fd.c            libft/ft_strjoin.c              libft/ft_strncmp.c              libft/ft_tolower.c \
              libft/ft_calloc.c               libft/ft_isprint.c              libft/ft_lstdelone_bonus.c      libft/ft_lstsize_bonus.c        libft/ft_memset.c               libft/ft_split.c                libft/ft_strlcat.c              libft/ft_strnstr.c              libft/ft_toupper.c \
              libft/ft_isalnum.c              libft/ft_itoa.c                 libft/ft_lstiter_bonus.c        libft/ft_memchr.c               libft/ft_putchar_fd.c           libft/ft_strchr.c               libft/ft_strlcpy.c              libft/ft_strrchr.c \
              libft/ft_isalpha.c              libft/ft_lstadd_back_bonus.c    libft/ft_lstlast_bonus.c        libft/ft_memcmp.c               libft/ft_putendl_fd.c           libft/ft_strdup.c               libft/ft_strlen.c               libft/ft_strtrim.c \
              ft_printf.c conversion_helpers.c flag_helpers.c ft_t_format_builder.c precision_helpers.c print_char.c util.c width_helpers.c print_str.c math_util.c math_util2.c util2.c print_void_ptr.c put_hex_fd.c print_int.c util3.c print_unsigned.c put_size_t_fd.c print_hexadecimal.c print_hexadecimal_2.c print_percent.c
#$(wildcard *.c libft/*.c)
OBJS		:= ${SRCS:.c=.o}
#LDFLAGS		:= -static -L./libft -lft

LIBFT		:= ./libft/libft.a

# SRCS_BONUS	:= foo.c

# OBJS_BONUS	:= ${SRCS_BONUS:.c=.o}

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -ggdb
RM			:= rm -f

LIBC		:= ar rc
LIBR		:= ranlib

.PHONY: all
all: ${NAME}

libft.a:
	make all bonus -C libft

#${NAME}: libft.a ${OBJS}
#	${LIBC} ${NAME} ${OBJS} ${LIBFT}
#	${LIBR} ${NAME}

bonus: all
	echo "bonus :)"

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}
	${LIBR} ${NAME}

# .PHONY: bonus
# bonus: ${OBJS} ${OBJS_BONUS}
# 	${LIBC} ${NAME} ${OBJS} ${OBJS_BONUS}
# 	${LIBR} ${NAME}

.PHONY: clean
clean:
	${RM} ${OBJS}

.PHONY: fclean
fclean: clean
	${RM} ${LIBFT}
	${RM} ${NAME}

.PHONY: re
re: fclean all
