# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alusnia <alusnia@student.42Warsaw.pl>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/05 19:16:03 by alusnia           #+#    #+#              #
#    Updated: 2026/02/16 12:53:08 by alusnia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftplus.a

CC				= cc

CFLAGS			=-g -Wall -Werror -Wextra 

INCS			= ./incs

OBJS_DIR 		= ./objs

GNL_DIR			= ./gnl

GNL_SRCS		= get_next_line.c get_next_line_utils.c

GNL_URL			= https://github.com/alusnia/42_gnl

INCLUDES		= -I$(BASE_DIR)/libft/incs -I$(BASE_DIR)/incs -I$(INCS) -I$(GNL_DIR)

BASE_DIR		= ./printf

BASE_URL		= https://github.com/alusnia/42_printf

BASE			= $(BASE_DIR)/libftprintf.a

OBJS			= $(addprefix $(OBJS_DIR)/, $(GNL_SRCS:.c=.o))

SEP				= "\n------------------------------------------------------------\n"

all: $(NAME)

$(NAME): $(BASE) $(OBJS)
	@echo $(SEP)
	@echo "Building $(NAME)..."
	@cp $(BASE) $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "Done!"
	@echo $(SEP)

$(BASE): | $(BASE_DIR)
	$(MAKE) -C $(BASE_DIR)

$(BASE_DIR):
	@echo $(SEP)
	@echo "Missing library libftprintf.a\nDownloading from $(BASE_URL)"
	@echo $(SEP)
	@mkdir -p $(BASE_DIR)
	@git clone $(BASE_URL) $(BASE_DIR)

$(OBJS_DIR)/%.o: $(GNL_DIR)/%.c | $(GNL_DIR)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_DIR)/%.c: | $(GNL_DIR)
	@:

$(GNL_DIR):
	@echo $(SEP)
	@echo "Missing GNL\nDownloading from $(GNL_URL)"
	@echo $(SEP)
	@mkdir -p $(GNL_DIR)
	@git clone $(GNL_URL) $(GNL_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@if [ -d $(BASE_DIR) ]; then $(MAKE) -C $(BASE_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@if [ -d $(BASE_DIR) ]; then $(MAKE) -C $(BASE_DIR) fclean; fi

del_lib:
	@echo $(SEP)
	@if [ -d $(BASE_DIR) ]; then \
		echo "Deleting library libftprintf"; \
		rm -rf $(BASE_DIR); \
	fi
	@if [ -d $(GNL_DIR) ]; then \
		echo "Deleting GNL"; \
		echo $(SEP); \
		rm -rf $(GNL_DIR); \
	fi
	
re: del_lib fclean all

.SECONDARY:
.PHONY: all clean fclean re del_lib