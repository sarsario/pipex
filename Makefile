# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 16:28:22 by osarsari          #+#    #+#              #
#    Updated: 2023/10/30 11:51:33 by osarsari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# The name of the executable
NAME	= pipex

# Compiler and compiling flags
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra

# Debug, use with`make DEBUG=1`
ifeq ($(DEBUG),1)
CFLAGS	+= -g3 -fsanitize=address
endif

# Folder names
SRCDIR	= src/
INCDIR	= includes/
OBJDIR	= obj/
LIB_DIR	= $(SRCDIR)lib/

# Add include folders
# INCLUDES = -I /opt/homebrew/Cellar/readline/8.2.1/include -I headers
CFLAGS	+= -I $(INCDIR) -I $(LIB_DIR)

# Linking stage flags
LDFLAGS = -L $(LIB_DIR) -lft
# LDFLAGS += -L/opt/homebrew/opt/readline/lib -lreadline -lhistory -ltermcap
# LDFLAGS += -L ~/.brew/opt/readline/lib -lreadline -lhistory -ltermcap

# List of source files (add your *.c files here)

SRCS =\
	$(SRCDIR)pipex.c \

HEADERS =\
	$(INCDIR)libft.h \

# String manipulation magic
SRC		:= $(notdir $(SRCS))
OBJ		:= $(SRC:.c=.o)
OBJS	:= $(addprefix $(OBJDIR), $(OBJ))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH := $(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)

# ================================== RULES =================================== #

all : $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Compiling
$(OBJDIR)%.o : %.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@


# Linking
$(NAME): $(OBJS) $(LIB_DIR)libft.a
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRCS)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

$(LIB_DIR)libft.a:
	@make -C $(LIB_DIR)

# Cleaning
clean :
	@make -C $(LIB_DIR) clean
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)

fclean : clean
	@make -C $(LIB_DIR) fclean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

# Special rule to force to remake everything
re : fclean all

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME) $(MAP)

# Special rule to check if files conform to the norm
norm :
	@printf "$(CY)=== Checking norm ===$(RC)\n"
	@norminette $(SRCDIR) $(HEADERS)

# This specifies the rules that does not correspond to any filename
.PHONY: all run clean fclean re $(LIBFT) norm