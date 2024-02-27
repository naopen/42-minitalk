# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 00:29:49 by nkannan           #+#    #+#              #
#    Updated: 2024/02/28 06:23:28 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PRINTF_DIR = ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
LIBTOOL = libtool -static -o
RM = rm -f

SRCS = ft_atoi.c ft_strlen.c ft_putstr_fd.c ft_putendl_fd.c ft_isdigit.c ft_strall.c
OBJS = $(SRCS:.c=.o)

MAKE = make

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF_LIB)
	$(LIBTOOL) $@ $(OBJS) $(PRINTF_LIB)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(RM) $(PRINTF_LIB)

re: fclean all

.PHONY: all clean fclean re
