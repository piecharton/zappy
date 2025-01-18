SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o .a

CXX = c++
CXXFLAGS = -I ./include  -Wall -Wextra -Werror -g -fsanitize=address

FILES =	main 			\
		generate_map	\
		parse_arg		\

SRCS	= $(addprefix $(SRCDIR), $(addsuffix .cpp, $(FILES)))

OBJS 	= $(addprefix $(OBJDIR), $(addsuffix .o, $(FILES)))

SRCDIR	= src/
OBJDIR  = obj/

NAME = Server

# Rule to compile source files into object files
# $(OBJDIR)%.o : Pattern for object files in the object directory
# src/%.cpp    : Corresponding source files in the src directory
# $<           : First prerequisite (source file)
# $@           : Target file (object file)
# -c           : Compile only, don't link
$(OBJDIR)%.o : $(SRCDIR)%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

all : $(NAME)

$(OBJDIR) :
	mkdir -p $@

$(NAME) :  $(OBJDIR) $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS)  -o $(NAME)
	
clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJS)

re: fclean all
