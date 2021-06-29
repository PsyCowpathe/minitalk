# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agirona <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/29 17:19:15 by agirona           #+#    #+#              #
#    Updated: 2021/06/29 18:14:34 by agirona          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME	= client

CLIENT_BONUS = bonus/client

CLIENT_SRCS	= client.c

CLIENT_OBJS	= $(CLIENT_SRCS:.c=.o)

CLIENT_SRCS_BONUS = client_bonus.c

CLIENT_OBJS_BONUS = $(CLIENT_SRCS_BONUS:.c=.o)

SERVER_NAME	= server

SERVER_BONUS = bonus/server

SERVER_SRCS	= server.c

SERVER_OBJS	= $(SERVER_SRCS:.c=.o)

SERVER_SRCS_BONUS = server_bonus.c

SERVER_OBJS_BONUS = $(SERVER_SRCS_BONUS:.c=.o)

INC		= minitalk.h

LIBFT = libft/libft.a

CFLAGS	= -Wall -Wextra -Werror -I $(INC)

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $< -o $@

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME) : $(LIBFT) $(CLIENT_OBJS)
			gcc $(CLIENT_OBJS) $(LIBFT) -o $(CLIENT_NAME)

$(SERVER_NAME) : $(LIBFT) $(SERVER_OBJS)
			gcc $(SERVER_OBJS) $(LIBFT) -o $(SERVER_NAME)

bonus:	bonus_create $(CLIENT_BONUS) $(SERVER_BONUS)

bonus_create :
	mkdir -p bonus

$(CLIENT_BONUS): $(LIBFT) $(CLIENT_OBJS_BONUS)
			gcc $(CLIENT_OBJS_BONUS) $(LIBFT) -o $(CLIENT_BONUS)

$(SERVER_BONUS): $(LIBFT) $(SERVER_OBJS_BONUS)
			gcc $(SERVER_OBJS_BONUS) $(LIBFT) -o $(SERVER_BONUS)

$(LIBFT) :
			$(MAKE) -C libft

clean:
			rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(SERVER_OBJS_BONUS) $(CLIENT_OBJS_BONUS)
			$(MAKE)	-C libft clean

fclean:		clean
			rm -f $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS) $(SERVER_BONUS)
			$(MAKE)	-C libft fclean

re:			fclean all

.PHONY:		all clean fclean re bonus bonus_create
