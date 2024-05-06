# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 14:59:21 by wlin              #+#    #+#              #
#    Updated: 2024/05/06 17:12:42 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pthread -g #-fsanitize=thread
SRC_DIR		:=	src

SRC_FILES	:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/input_validate.c \
				$(SRC_DIR)/dining.c \
				$(SRC_DIR)/routine.c \
				$(SRC_DIR)/utils.c \

OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

%.o:%.c		src/philo.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@
-include $(DEP_FILES)

clean:
		rm -rf $(OBJ_FILES) $(DEP_FILES)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
