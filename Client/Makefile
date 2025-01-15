SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o .a

CXX = c++
CXXFLAGS = -I ./include  -Wall -Wextra -Werror -g

FILES =	main

SRCS	= $(addprefix src/, $(addsuffix .cpp, $(FILES)))

OBJS 	= $(addprefix src/, $(addsuffix .o, $(FILES)))

OBJDIR  = obj/

NAME = Client

.cpp.o :
	@${CXX} ${CXXFLAGS} -c $< -o ${<:.cpp=.o}

all : $(NAME)

$(OBJDIR) :
	mkdir -p $@

$(NAME) :  $(OBJDIR) $(OBJS)
	@$(CXX) $(OBJS) $(CXXFLAGS)  -o $(NAME)
	
clean:
	@rm -f $(OBJS)
	@rm -f $(NAME)

fclean: clean

re: fclean all
