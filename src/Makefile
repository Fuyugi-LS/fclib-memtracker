# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/15 17:41:24 by nsongsit          #+#    #+#              #
#    Updated: 2025/11/15 17:47:33 by nsongsit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmemtracker.a

CC			= cc
FLAGS		= -Wall -Wextra -Werror
AR			= ar rcs

HEADERS		= memtracker.h \
			memtracker_utils.h

SRCS		= mem_free_all.c \
			mem_free_partial.c \
			mem_perror.c \
			mem_register.c \
			mem_storage.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building library $(NAME)..."
	@$(AR) $(NAME) $(OBJS)
	@echo "$(NAME) is ready."

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)

fclean: clean
	@echo "Cleaning library file..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
