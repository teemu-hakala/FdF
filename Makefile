# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 11:07:24 by thakala           #+#    #+#              #
#    Updated: 2022/03/24 14:16:21 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
MATH_LIB = m

FILES = \
	fdf

LIBFT_NAME = libft
LIBFT_DIR = libft
LIBFT_OBJECTS_DIR = $(LIBFT_DIR)/objects
LIBFT_OBJECT_PATHS = $(addsuffix .o, $(addprefix $(LIBFT_OBJECTS_DIR), \
	ft_abs \
	ft_atoi \
	ft_bzero \
	ft_isalnum \
	ft_isalpha \
	ft_isascii \
	ft_isdigit \
	ft_isprint \
	ft_isspace \
	ft_itoa \
	ft_lstadd \
	ft_lstdel \
	ft_lstdelone \
	ft_lstiter \
	ft_lstmap \
	ft_lstnew \
	ft_lstpop \
	ft_memalloc \
	ft_memccpy \
	ft_memchr \
	ft_memcmp \
	ft_memcpy \
	ft_memdel \
	ft_memdup \
	ft_memjoin \
	ft_memmove \
	ft_memrplc \
	ft_memset \
	ft_putchar \
	ft_putchar_fd \
	ft_putendl \
	ft_putendl_fd \
	ft_putnbr \
	ft_putnbr_fd \
	ft_putstr \
	ft_putstr_fd \
	ft_sign \
	ft_strcat \
	ft_strchr \
	ft_strclr \
	ft_strcmp \
	ft_strcpy \
	ft_strcspn \
	ft_strdel \
	ft_strdup \
	ft_strequ \
	ft_striter \
	ft_striteri \
	ft_strjoin \
	ft_strlcat \
	ft_strlcpy \
	ft_strlen \
	ft_strmap \
	ft_strmapi \
	ft_strncat \
	ft_strncmp \
	ft_strncpy \
	ft_strnequ \
	ft_strnew \
	ft_strnstr \
	ft_strpbrk \
	ft_strrchr \
	ft_strsep \
	ft_strsplit \
	ft_strspn \
	ft_strspnsep \
	ft_strstr \
	ft_strsub \
	ft_strtrim \
	ft_tolower \
	ft_toupper \
	get_next_line))

FILES = \
	convert_character \
	convert_float \
	convert_hexadecimal \
	convert_octal \
	convert_pointer \
	convert_signed \
	convert_string \
	convert_unsigned \
	ft_printf

SOURCES = sources
OBJECTS = objects
INCLUDES = includes
LIBRARIES = libraries
DEBUG_OBJECTS = debug_objects

FOLDER_LIST = \
	$(SOURCES) \
	$(OBJECTS) \
	$(INCLUDES) \
	$(LIBRARIES) \
	$(DEBUG_OBJECTS)

H_FILES = ft_printf

C_PATHS = $(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
H_PATHS = $(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
INCLUSIONS = $(foreach inc, $(INCLUDES), -I $(inc))
O_PATHS = $(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))

CC = clang
CCFLAGS = -Wall -Wextra -Werror -Wconversion -O3
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

.PHONY: all
all: $(NAME)

$(NAME): .pre_requisites $(O_PATHS) Makefile
	touch .pre_requisites
	$(CC) $(CCFLAGS) -l$(MATH_LIB) $(MLXFLAGS)

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	$(CC) $(CCFLAGS) $(INCLUSIONS) -c $< -o $@

.pre_requisites: $(LIBFT_NAME) $(FOLDER_LIST) $(H_PATHS) $(C_PATHS)

.PHONY: $(LIBFT_NAME)
$(LIBFT_NAME):
	make -C $(LIBFT_DIR)

$(FOLDER_LIST):
	mkdir -p $@

$(H_PATHS):
	touch $@

$(C_PATHS):
	touch $@

.PHONY: clean
clean:
	/bin/rm -f $(O_PATHS)
	make -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

.PHONY: re
re: fclean all
