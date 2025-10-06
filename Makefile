CFLAGS		=	-std=c++98 -MMD -MP# -Wall -Wextra -Werror

COMPILER	=	c++

SRCS		=	main.cpp Client.cpp helper.cpp Server.cpp Channel.cpp

OBJDIR		=	objs/
OBJS		=	$(addprefix $(OBJDIR), $(SRCS:.cpp=.o))
DEPS		=	$(addprefix $(OBJDIR), $(SRCS:.cpp=.d))

NAME		=	irc

all : $(NAME)

$(NAME)	:	$(OBJS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o	:	%.cpp
	mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) -c $< -o $@

-include $(DEPS)

c : clean
clean :
	rm -rf $(OBJS) $(DEPS) $(OBJDIR)

f : fclean
fclean : clean
	rm -rf $(NAME)

re : fclean all

run : all clean
	./$(NAME)

.phony : all c clean f fclean re run