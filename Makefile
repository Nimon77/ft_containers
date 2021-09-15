# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsimon <nsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/02 15:06:00 by nsimon            #+#    #+#              #
#    Updated: 2021/09/15 02:32:17 by nsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_containers
CC			= clang++

# Compiler & Preprocessor flags
CFLAGS		+= -Wall -Werror -Wextra -std=c++98
CPPFLAGS	+= -I containers/
MAKEFLAGS	+= --no-print-directory

# Recompile on headers/Makefile changes
HEADERS		= containers/$(NAME).hpp
#DEPS		= $(HEADERS) Makefile libft/Makefile

# Source files
SRC_PATH	= tests/
SRC_NAME	= main test_iterator test_vector test_reverse_iterator

# Object files
OBJ_PATH	= obj/
OBJ_NAME	= $(addsuffix .o, $(SRC_NAME))
OBJ			= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Library
#LIB_PATH	= libft
#LIB_NAME	= ft
#LIB_FILE	= $(LIB_PATH)/lib$(LIB_NAME).a
#LIB_FLAGS	= -L $(LIB_PATH) -l $(LIB_NAME)

# Colors
C_RESET		= \033[0m
C_PENDING	= \033[0;36m
C_SUCCESS	= \033[0;32m

# Escape Sequences (ANSI/VT100)
ES_ERASE	= "\033[A\033[K\033[A"
ERASE		= $(ECHO) $(ES_ERASE)

# Hide STD/ERR and prevent Make from returning non-zero code
HIDE_STD	= > /dev/null
HIDE_ERR	= 2> /dev/null || true

# Multi platforms 
ECHO 		= echo
ifeq ($(shell uname),Linux)
	ECHO	+= -e
endif

GREP		= grep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn}

NORMINETTE	= norminette
#NORMINETTE	= ~/.norminette/norminette.rb

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FLAGS) -o $(NAME)
	@$(ERASE)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_SUCCESS)✅ $(C_RESET)]"
	@$(ECHO) "$(C_SUCCESS)All done, compilation successful! 👌 $(C_RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(DEPS)
	@mkdir -p $(OBJ_PATH)/builtins $(HIDE_ERR)
	@$(ERASE)
	@$(ECHO) "$(NAME)\t[$(C_PENDING)⏳ $(C_RESET)]"
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@$(ERASE)

clean:
	@$(RM) -r $(OBJ_PATH) $(HIDE_ERR)
	@$(RM) -r $(NAME).dSYM $(HIDE_ERR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

norm:
	@$(NORMINETTE) include/ src/ | $(GREP) -v 'Not a valid file' | $(GREP) -EB1 'Error|Warning' || true

.PHONY: clean fclean all re norm
