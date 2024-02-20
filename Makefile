# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 02:33:18 by nkannan           #+#    #+#              #
#    Updated: 2024/02/21 02:33:28 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# コンパイラとフラグの設定
CC = cc
CFLAGS = -Wall -Wextra -Werror

# ソースファイルとオブジェクトファイル
SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)

# プログラム名
NAME_CLIENT = client
NAME_SERVER = server

# ft_printfライブラリのパス
LIBFTPRINTF = ft_printf/libftprintf.a

# ルール定義
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFTPRINTF) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFTPRINTF) -o $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFTPRINTF) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFTPRINTF) -o $(NAME_SERVER)

$(LIBFTPRINTF):
	make -C ft_printf

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C ft_printf clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
