# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 11:07:24 by thakala           #+#    #+#              #
#    Updated: 2022/03/24 11:20:48 by thakala          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

MATH_LIB = m

#.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -l$(MATH_LIB)


#.PHONY: clean
#	make -C libft clean

#.PHONY: fclean
#	make -C libft fclean

#.PHONY: re
#re: fclean all
