NAME		=	serv
CXX		=	c++
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98

INCFLAGS	=	-Iinclude

SRCDIR		=	src
SRCS		=	$(addprefix $(SRCDIR)/, \
							$(addprefix Config/, \
									Config.cpp \
									ConfigParser.cpp \
							) \
				main.cpp \
				Server.cpp \
				SockFd.cpp \
			)

OBJDIR		=	obj
OBJS		=	$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

all:	$(NAME)
$(NAME):	$(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
