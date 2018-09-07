##
## EPITECH PROJECT, 2018
## bstd
## File description:
## makefile
##

CXX	=	g++

CPPFLAGS	+=	-Idll -Iecs -IpathFinding

CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-std=c++17

LDFLAGS		+=
LDLIBS		+=	-ldl

SRCS		=	bstdTester.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = tester.out

ECHO = -@printf
GREEN = "\x1b[32m"
RESET = "\x1b[0m"

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	$(ECHO) $(GREEN)"✓ Build successful !"$(RESET)"\n"

clean:
	$(RM) $(OBJS)
	$(ECHO) $(GREEN)"✓ Object files cleaned..."$(RESET)"\n"

fclean: clean
	$(RM) $(NAME)
	$(ECHO) $(GREEN)"✓ Binary files cleaned..."$(RESET)"\n"

re: fclean all

.PHONY: all clean fclean re
