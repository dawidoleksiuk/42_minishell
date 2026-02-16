# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 20:07:11 by doleksiu          #+#    #+#              #
#    Updated: 2026/02/16 13:03:16 by alusnia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS =-g -Wall -Werror -Wextra -I$(LIB_DIR)/incs -I$(INCS_DIR)
NAME = minishell

LIB_DIR		= ./lib

LIB			= $(LIB_DIR)/libftplus.a

SRC_DIR = ./srcs
OBJS_DIR = ./objs
INCS_DIR = ./includes
SRCS = minishell.c clean_exit.c init.c signals.c tokenizer.c tokenizer_2.c \
		parser.c expander.c redirection.c executor.c builtins_1.c
OBJS = $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))
INCS = $(INCS_DIR)/minishell.h $(INCS_DIR)/parser.h

all: $(LIB) $(NAME)
 
$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -lhistory -o $(NAME)
	@echo "$(NAME): Done!"

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean: 
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

del_lib:
	@echo $(SEP)
	@echo "Deleting library libftplus..."
	@echo $(SEP)
	@$(MAKE) -C $(LIB_DIR) del_lib

.PHONY: all clean fclean re del_lib