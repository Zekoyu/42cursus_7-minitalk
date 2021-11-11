SRCS_CLIENT = client.c

SRCS_CLIENT_BONUS = client_bonus.c

SRCS_SERVER = server.c

SRCS_SERVER_BONUS = server_bonus.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

OBJS_SERVER = $(SRCS_SERVER:.c=.o)

OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

ifdef INCLUDE_BONUSES
OBJS_CLIENT_FINAL = $(OBJS_CLIENT_BONUS)
OBJS_SERVER_FINAL = $(OBJS_SERVER_BONUS)
else
OBJS_CLIENT_FINAL = $(OBJS_CLIENT)
OBJS_SERVER_FINAL = $(OBJS_SERVER)
endif

NAME = server

CC = gcc

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS_CLIENT_FINAL) $(OBJS_SERVER_FINAL)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_FINAL) -o client
	$(CC) $(CFLAGS) $(OBJS_SERVER_FINAL) -o server

bonus:		
	$(MAKE) INCLUDE_BONUSES=1

all:		$(NAME)

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER) $(OBJS_SERVER_BONUS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.PHONY:	all clean fclean re bonus