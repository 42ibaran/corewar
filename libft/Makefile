# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaran <ibaran@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 14:57:26 by ibaran            #+#    #+#              #
#    Updated: 2019/07/10 15:09:27 by ibaran           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME)
.PHONY: clean
.PHONY: fclean
.PHONY: re

VPATH:= ./sources/ ./objects/ ./includes/

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

NAME := libft.a

CC := gcc
INCLUDES := -I includes/
FLAGS := -Wall -Wextra -Werror

SRCS_PATH := ./sources/
SRCS_NAME := \
ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c \
ft_lstfold.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
ft_power.c ft_printwordtab.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strsplitlst.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
ft_toupper.c ft_ctoa.c ft_abs.c ft_itoa_base.c ft_strtolower.c ft_ftoa.c \
ft_sumstrstr.c ft_min.c ft_max.c ft_nctoa.c ft_strtoupper.c ft_strndup.c \
get_next_line.c ft_printinttab.c ft_atoi_base.c ft_strisnum.c ft_swap.c \
ft_freewordtab.c ft_strjoinfree.c

PRINTF_SRCS_PATH := ./sources/ft_printf/
PRINTF_SRCS_NAME = \
ft_printf_main.c for_di.c for_f.c for_uoxx.c for_csppercent.c ft_filling.c \
ft_getting_argument.c ft_importants.c ft_strncpy_zero.c ft_color.c \
ft_argument_value.c ft_dupexit.c

OBJS_PATH := ./objects/
OBJS_NAME := $(SRCS_NAME:.c=.o)
PRINTF_OBJS_NAME := $(PRINTF_SRCS_NAME:.c=.o)

OBJS := $(patsubst %,$(OBJS_PATH)%,$(OBJS_NAME))
OBJS += $(patsubst %,$(OBJS_PATH)%,$(PRINTF_OBJS_NAME))

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo [CC] $<
	@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

$(OBJS_PATH)%.o: $(PRINTF_SRCS_PATH)%.c
	@echo [CC] $<
	@$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

$(NAME): $(OBJS) $(PRINTF_OBJS)
	@ar rc $@ $^
	@echo "$(GREEN)[Libft Compiled]$(DEFAULT)"

#clean:
#	@/bin/rm -f $(OBJS)
#	@echo "$(YELLOW)[Libft Objects Removed]$(DEFAULT)"
#
#fclean: clean
#	@/bin/rm -f $(NAME)
#	@echo "$(RED)[Libft Archive Removed]$(DEFAULT)"

clean:
	@/bin/rm -f $(OBJS)
	@echo "$(YELLOW)[Libft Objects Removed]$(DEFAULT)"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "$(RED)[Libft Archive Removed]$(DEFAULT)"

re: fclean all
