# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ephe <ephe@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/10 13:28:55 by ibaran            #+#    #+#              #
#    Updated: 2019/09/09 15:58:04 by ephe             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM					:=	asm
VM					:=	corewar

VPATH				:=	./sources/ ./objects/ ./includes/

SRC_NAME_ASM		:=	asm.c								\
						asm_read_and_save.c					\
						asm_define_word.c					\
						asm_definition_1.c					\
						asm_definition_2.c					\
						asm_errors.c						\
						asm_init_1.c						\
						asm_init_2.c						\
						asm_debug.c							\
						asm_new_struct.c					\
						asm_translator.c					\
						asm_write_file.c					\
						asm_put_name_and_comment.c			\
						asm_prepare_operations.c			\
						asm_put_code.c						\
						asm_process_negative_arg_val.c		\
						asm_check_operations_1.c			\
						asm_check_operations_2.c			\
						asm_check_operations_3.c			\
						asm_check_operations_4.c			\
						asm_word_is_what.c					\
						asm_get_f_arr.c						\
						asm_check_arg.c						\
						asm_get_operation_parameters.c		\
						asm_get_label_distance.c			\
						asm_free.c

SRC_NAME_VM			:=	vm.c								\
						usage.c								\
						parse_argv.c						\
						init_champ.c						\
						operate.c							\
						operate2.c							\
						operate3.c							\
						operate4.c							\
						cycles.c							\
						utilities.c							\
						load_field.c						\
						op.c								\
						process.c							\
						param_setup.c						\
						operations1.c						\
						operations2.c						\
						operations3.c						\
						operations4.c						\
						dump.c								\
						intro.c								\
						argv_utilities.c					\
						parse_utilities.c					\
						visu_utilities.c					\
						visu_init.c							\
						visu_legend.c						\
						visu_cycles.c						\
						visu.c								\
						exit.c

HEAD_NAME_ASM		:=	asm.h
HEAD_NAME_VM		:=	vm.h
HEAD_NAME_COMMON	:=	op.h
HEAD_NAME_ASM		+=	$(HEAD_NAME_COMMON)
HEAD_NAME_VM		+=	$(HEAD_NAME_COMMON)

LIB_NAME			:=	libft.a

OBJ_NAME_ASM		:=	$(SRC_NAME_ASM:.c=.o)
OBJ_NAME_VM			:=	$(SRC_NAME_VM:.c=.o)

SRC_PATH			:=	./sources
HEAD_PATH			:=	./includes
LIB_PATH			:=	./libft

SRC_PATH_ASM		:=	$(SRC_PATH)/asm
SRC_PATH_VM			:=	$(SRC_PATH)/vm

CFLAGS				:=	-Wall -Wextra -Werror -O3 -flto \
						$(shell pkg-config --cflags SDL2)		\
						$(shell pkg-config --cflags SDL2_ttf)

OBJ_PATH			:=	./objects

SRC_ASM				:=	$(addprefix $(SRC_PATH_ASM)/, $(SRC_NAME_ASM))
SRC_VM				:=	$(addprefix $(SRC_PATH_VM)/, $(SRC_NAME_ASM))

OBJ_ASM				:=	$(addprefix $(OBJ_PATH)/, $(OBJ_NAME_ASM))
OBJ_VM				:=	$(addprefix $(OBJ_PATH)/, $(OBJ_NAME_VM))

HEAD_ASM			:=	$(addprefix $(HEAD_PATH)/, $(HEAD_NAME_ASM))
HEAD_VM				:=	$(addprefix $(HEAD_PATH)/, $(HEAD_NAME_VM))

OBJ					:=	$(OBJ_ASM) $(OBJ_VM)

LIBFT				:=	$(LIB_PATH)/$(LIB_NAME)

CC					:=	gcc
CPPFLAGS			:=	-I $(HEAD_PATH)								\
						-I $(LIB_PATH)/includes						

LIBS_ASM			:=	-L$(LIB_PATH) -lft
LIBS_VM				:=	$(LIBS_ASM)									\
						$(shell pkg-config --libs SDL2) 			\
						$(shell pkg-config --libs SDL2_ttf)

RED					:=	\033[0;31m
GREEN				:=	\033[0;32m
YELLOW				:=	\033[1;33m
DEFAULT				:=	\033[0m

all: $(ASM) $(VM)

$(ASM): $(LIBFT) $(OBJ_ASM) $(HEAD_ASM)
	@$(CC) $(CFLAGS) $(LIBS_ASM) $(CPPFLAGS) $(OBJ_ASM) -o $@
	@echo "$(GREEN)[$@ Compiled]$(DEFAULT)"

$(VM): $(LIBFT) $(OBJ_VM) $(HEAD_VM)
	@$(CC) $(CFLAGS) $(LIBS_VM) $(CPPFLAGS) $(OBJ_VM) -o $@
	@echo "$(GREEN)[$@ Compiled]$(DEFAULT)"

$(OBJ_PATH)/%.o : $(SRC_PATH_ASM)/%.c $(HEAD_ASM)
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH_VM)/%.c $(HEAD_VM)
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIB_PATH)

norm:
	@norminette **/*.[ch]

clean:
	@$(MAKE) -C $(LIB_PATH) $@
	@rm -f $(OBJ)
	@echo "$(YELLOW)[Corewar Objects Removed]$(DEFAULT)"

fclean: clean
	@$(MAKE) -C $(LIB_PATH) $@
	@rm -f $(ASM) $(VM)
	@echo "$(RED)[Corewar exe Removed]$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re norm
