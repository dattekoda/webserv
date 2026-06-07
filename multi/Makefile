NAME		=	serv
CXX		=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98

INCFLAGS	=	-Iinclude

SRCS		=	main.cpp \
			SocketFD.cpp \
			Server.cpp

OBJS		=	$(SRCS:.cpp=.o)


all:	$(NAME)
$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
