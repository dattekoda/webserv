NAME	=	server
CC	=	cc

CFLAGS	=	-Wall

SRCS	=	main.c send_recv.c server4.c server_socket.c

OBJS	=	$(SRCS:.c=.o)

RM	=	rm -f

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
