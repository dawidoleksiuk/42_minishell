# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: doleksiu <doleksiu@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 20:07:11 by doleksiu          #+#    #+#              #
#    Updated: 2026/01/19 17:44:47 by doleksiu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS =-g -Wall -Werror -Wextra -I$(INCS_DIR) -I./libft
NAME = minishell

SRC_DIR = ./srcs
OBJS_DIR = ./objs
INCS_DIR = ./includes
LIBFT = ./libft/libft.a
SRCS = minishell.c clean_exit.c init.c signals.c tokenizer.c tokenizer_2.c \
		parser.c expander.c
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
INCS = $(INCS_DIR)/minishell.h $(INCS_DIR)/parser.h

all: $(LIBFT) $(NAME)
 
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lhistory -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean: 
	rm -rf $(OBJS_DIR)
	@$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
