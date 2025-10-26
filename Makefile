CFLAGS		=	-std=c++98 -MMD -MP# -Wall -Wextra -Werror

COMPILER	=	c++

SRCS		=	main.cpp Client.cpp helper.cpp Server.cpp Channel.cpp $(addprefix $(COMMANDSDIR), $(COMMANDSSRC))
COMMANDSDIR	=	commands/
COMMANDSSRC	=	CapCommand.cpp Command.cpp command_parser.cpp InviteCommand.cpp JoinCommand.cpp KickCommand.cpp ModeCommand.cpp NickCommand.cpp PartCommand.cpp PassCommand.cpp PingCommand.cpp PrivmsgCommand.cpp QuitCommand.cpp TopicCommand.cpp UserCommand.cpp IrcReplies.cpp

OBJDIR		=	objs/
OBJS		=	$(addprefix $(OBJDIR), $(SRCS:.cpp=.o))
DEPS		=	$(addprefix $(OBJDIR), $(SRCS:.cpp=.d))

NAME		=	ircserv

all : $(NAME)

$(NAME)	:	$(OBJS)
	@$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\e[1;32mCOMPILED\e[0m"

$(OBJDIR)%.o	:	%.cpp
	@mkdir -p $(dir $@)
	@$(COMPILER) $(CFLAGS) -c $< -o $@

-include $(DEPS)

c : clean
clean :
	@rm -rf $(OBJS) $(DEPS) $(OBJDIR)

f : fclean
fclean : clean
	@rm -rf $(NAME)

re : fclean all

run : all clean
	@./$(NAME) 3333 SAFEME

.phony : all c clean f fclean re run