# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/31 11:42:48 by thakala           #+#    #+#              #
#    Updated: 2022/01/02 09:08:11 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FUNCTIONS = \
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
	ft_memrplc

SRCS = $(foreach src, $(FUNCTIONS), $(addsuffix .c, $(src)))

OBJS = $(foreach obj, $(FUNCTIONS), $(addsuffix .o, $(obj)))

COMP_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(COMP_FLAGS) -c $(SRCS)
	ar rcs $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
