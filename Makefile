# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 20:07:11 by doleksiu          #+#    #+#              #
#    Updated: 2026/04/15 13:38:11 by alusnia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I$(LIB_DIR)/incs -I$(INCS_DIR)
NAME = minishell

LIB_DIR     = ./lib
LIB         = $(LIB_DIR)/libftplus.a

SRC_DIR     = ./srcs
OBJS_DIR    = ./objs
INCS_DIR    = ./includes

CORE_DIR	= core
HASH_DIR    = hash_table
EXEC_DIR    = executor
PARS_DIR    = parser
TOK_DIR     = tokenizer
BLT_DIR     = builtins

CORE_FILES  = minishell.c clean_exit.c init.c signals.c
HASH_FILES  = nodes_operations.c core.c operations.c \
				sort.c utils.c methods.c
EXEC_FILES  = redirection.c executor.c
PARS_FILES  = parser.c expander.c
TOK_FILES   = tokenizer.c tokenizer_utils.c
BLT_FILES   = rest.c table_related.c

SRCS = $(addprefix $(SRC_DIR)/$(CORE_DIR)/, $(CORE_FILES)) \
       $(addprefix $(SRC_DIR)/$(HASH_DIR)/, $(HASH_FILES)) \
       $(addprefix $(SRC_DIR)/$(EXEC_DIR)/, $(EXEC_FILES)) \
       $(addprefix $(SRC_DIR)/$(PARS_DIR)/, $(PARS_FILES)) \
       $(addprefix $(SRC_DIR)/$(TOK_DIR)/, $(TOK_FILES)) \
       $(addprefix $(SRC_DIR)/$(BLT_DIR)/, $(BLT_FILES))

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS = $(INCS_DIR)/minishell.h $(INCS_DIR)/parser.h

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@


all: $(LIB) $(NAME)
 
$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -lreadline -lhistory -o $(NAME)
	@echo "$(NAME): Done!"

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean: 
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: del_lib fclean all

del_lib:
	@echo $(SEP)
	@echo "Deleting library libftplus..."
	@echo $(SEP)
	@$(MAKE) -C $(LIB_DIR) del_lib

.PHONY: all clean fclean re del_lib