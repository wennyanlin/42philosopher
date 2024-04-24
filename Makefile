# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 14:59:21 by wlin              #+#    #+#              #
#    Updated: 2024/04/24 17:09:29 by wlin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread -g
SRC_DIR		:=	src

SRC_FILES	:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/input_validate.c \

OBJ_FILES	=	$(SRC_FILES:.c=.o)
DEP_FILES	=	$(OBJ_FILES:.o=.d)

%.o:%.c		src/philo.h Makefile
			$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

-include $(DEP_FILES)
$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@

clean:
		rm -rf $(OBJ_FILES) $(DEP_FILES)

fclean:	clean
		rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
