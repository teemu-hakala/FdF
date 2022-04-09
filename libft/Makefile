# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 11:42:48 by thakala           #+#    #+#              #
#    Updated: 2022/04/09 11:07:30 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_NAME = libft.a

FILES = \
	ft_memset \
	ft_bzero \
	ft_memcpy \
	ft_memccpy \
	ft_memmove \
	ft_memchr \
	ft_memcmp \
	ft_strlen \
	ft_strdup \
	ft_strcpy \
	ft_strncpy \
	ft_strcat \
	ft_strncat \
	ft_strlcat \
	ft_strchr \
	ft_strrchr \
	ft_strstr \
	ft_strnstr \
	ft_strcmp \
	ft_strncmp \
	ft_atoi \
	ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_toupper \
	ft_tolower \
	ft_memalloc \
	ft_memdel \
	ft_strnew \
	ft_strdel \
	ft_strclr \
	ft_striter \
	ft_striteri \
	ft_strmap \
	ft_strmapi \
	ft_strequ \
	ft_strnequ \
	ft_strsub \
	ft_strjoin \
	ft_strtrim \
	ft_strsplit \
	ft_itoa \
	ft_putchar \
	ft_putstr \
	ft_putendl \
	ft_putnbr \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_lstnew \
	ft_lstdelone \
	ft_lstdel \
	ft_lstadd \
	ft_lstiter \
	ft_lstmap \
	ft_memdup \
	ft_isspace \
	ft_strpbrk \
	ft_strsep \
	ft_strspn \
	ft_strcspn \
	ft_strlcpy \
	ft_strspnsep \
	ft_memjoin \
	ft_sign \
	ft_abs \
	ft_lstpop \
	ft_memrplc \
	get_next_line

SRCS = $(addsuffix .c, $(FILES))

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))
OBJ_DIR = objects

FOLDER_LIST = $(OBJ_DIR)

H_PATHS = includes/libft.h includes/get_next_line.h

CC = clang

CCFLAGS = -Wall -Wextra -Werror

all: $(CCFLAGS) := $(CCFLAGS) -O3 -flto
all: $(LIBFT_NAME)

all-debug: $(LIBFT_NAME)

$(LIBFT_NAME): .pre_requisites $(OBJS) Makefile
	touch .pre_requisites
	ar rcs $(LIBFT_NAME) $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o:%.c $(H_PATHS) Makefile
	$(CC) $(CCFLAGS) -c $< -o $@

.pre_requisites: $(FOLDER_LIST)

$(FOLDER_LIST):
	mkdir -p $@

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(LIBFT_NAME) .pre_requisites
	/bin/rm -rf $(OBJ_DIR)

re: fclean all

debug: $(CCFLAGS) := $(CCFLAGS) -g
debug: fclean all-debug
	@echo "libft debug rule called!"
