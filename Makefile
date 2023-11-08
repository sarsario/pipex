# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: osarsari <osarsari@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 16:28:22 by osarsari          #+#    #+#              #
#    Updated: 2023/11/08 08:54:21 by osarsari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= VARIABLES ================================ #

# The name of the executable
NAME	= pipex
BONUS	= pipex_bonus

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
SRCBONUSDIR = bonus_src/
INCDIRBONUS = bonus_includes/
OBJDIRBONUS = bonus_obj/
LIB_DIRBONUS = $(SRCBONUSDIR)lib/

# Add include folders
CFLAGS	+= -I $(INCDIR) -I $(LIB_DIR)

# Linking stage flags
LDFLAGS = -L $(LIB_DIR) -lft

# List of source files (add your *.c files here)

SRCS =\
	$(SRCDIR)pipex.c \
	$(SRCDIR)free.c \
	$(SRCDIR)find_cmd.c \

SRCSBONUS =\
	$(SRCBONUSDIR)pipex_bonus.c \
	$(SRCBONUSDIR)parse_args.c \
	$(SRCBONUSDIR)exec_lst.c \

HEADERS =\
	$(INCDIR)libft.h \
	$(INCDIR)pipex.h \

HEADERSBONUS =\
	$(INCDIRBONUS)libft.h \
	$(INCDIRBONUS)pipex_bonus.h \

# String manipulation magic
SRC			:= $(notdir $(SRCS))
OBJ			:= $(SRC:.c=.o)
OBJS		:= $(addprefix $(OBJDIR), $(OBJ))
SRCBONUS	:= $(notdir $(SRCSBONUS))
OBJBONUS	:= $(SRCBONUS:.c=.o)
OBJSBONUS	:= $(addprefix $(OBJDIRBONUS), $(OBJBONUS))

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

# Implicit rules
VPATH :=	$(SRCDIR) $(OBJDIR) $(shell find $(SRCDIR) -type d)\
			$(SRCBONUSDIR) $(OBJDIRBONUS) $(shell find $(SRCBONUSDIR) -type d)

# ================================== RULES =================================== #

all : $(OBJDIR) $(NAME)

bonus : $(OBJDIRBONUS) $(BONUS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIRBONUS):
	@mkdir -p $(OBJDIRBONUS)

# Compiling
$(OBJDIR)%.o : %.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIRBONUS)%.o : %.c $(HEADERSBONUS)
	@mkdir -p $(OBJDIRBONUS)
	@printf "$(GR)+$(RC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking
$(NAME): $(OBJS) $(LIB_DIR)libft.a
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRCS)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(NAME)$(RC)\n"

$(BONUS): $(OBJSBONUS) $(LIB_DIRBONUS)libft.a
	@printf "\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ===\n--- $(SRCSBONUS)$(RC)\n"
	@$(CC) $(CFLAGS) $(OBJSBONUS) $(LDFLAGS) -o $(BONUS)
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\n--- $(BONUS)$(RC)\n"

$(LIB_DIR)libft.a:
	@make -C $(LIB_DIR)

$(LIB_DIRBONUS)libft.a:
	@make -C $(LIB_DIRBONUS)

# Cleaning
clean :
	@make -C $(LIB_DIR) clean
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\n"
	@rm -rf $(OBJDIR)

cleanbonus :
	@make -C $(LIB_DIRBONUS) clean
	@printf "$(RE)--- Removing $(OBJDIRBONUS)$(RC)\n"
	@rm -rf $(OBJDIRBONUS)

fclean : clean
	@make -C $(LIB_DIR) fclean
	@printf "$(RE)--- Removing $(NAME)$(RC)\n"
	@rm -f $(NAME)

fcleanbonus : cleanbonus
	@make -C $(LIB_DIRBONUS) fclean
	@printf "$(RE)--- Removing $(BONUS)$(RC)\n"
	@rm -f $(BONUS)

# Special rule to force to remake everything
re : fclean all

rebonus : fcleanbonus bonus

# This runs the program
run : $(NAME)
	@printf "$(CY)>>> Running $(NAME)$(RC)\n"
	./$(NAME) $(MAP)

# Special rule to check if files conform to the norm
norm :
	@printf "$(CY)=== Checking norm ===$(RC)\n"
	@norminette $(SRCDIR) $(HEADERS)

normbonus :
	@printf "$(CY)=== Checking norm ===$(RC)\n"
	@norminette $(SRCBONUSDIR) $(HEADERSBONUS)

# This specifies the rules that does not correspond to any filename
.PHONY: all run clean fclean re $(LIBFT) norm bonus cleanbonus fcleanbonus rebonus normbonus