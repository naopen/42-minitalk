# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 02:33:18 by nkannan           #+#    #+#              #
#    Updated: 2024/02/28 06:40:55 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBFT_DIR = libft

SRC_CLIENT = client.c
SRC_SERVER = server.c
SRC_CLIENT_BONUS = client_bonus.c
SRC_SERVER_BONUS = server_bonus.c

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)

MAKE = make

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(LIBFT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

.PHONY: all clean fclean re bonus
