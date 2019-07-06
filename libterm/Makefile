################################################################################
# Basics #######################################################################
NAME	:=	libterm.a
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--leak-check=full --track-origins=yes --show-leak-kinds=all \
				--show-reachable=no

# Libraries #####################################################################
LIBFT_DIR	:= ../libft

LIB_INCL	:=	-L $(LIBFT_DIR) -lft -ltermcap
LIBFT_A		:=	$(LIBFT_DIR)/libft.a


LIBS		:= $(LIBFT_A)

# Includes  #####################################################################
INCL_DIR	:=	includes $(LIBFT_DIR)/includes
INCL_CMD	:=	$(addprefix -I,$(INCL_DIR))

INCL_FILES	:=	libterm.h cursor.h

INCLS		:=	$(addprefix includes/,$(INCL_FILES))

# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	ERRORS_DIR		:=	errors
	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(ERRORS_DIR)

#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	execute_cap.c termcap_settings.c check_caps.c \
				restore_init_cursor.c
	#srcs subfiles names
	ERRORS_FILES	:=	error_attr.c error_caps.c error_getenv.c \
						error_tgoto.c error_isatty.c error_tgetent.c

#list of all .c files
C_FILES	:=	$(SRC_FILES) $(ERRORS_FILES)


# Complete path of each .c files ###############################################
SRC_PATH		:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
ERRORS_PATH		:=	$(addprefix $(ERRORS_DIR)/,$(ERRORS_FILES))

#list of all "path/*.c"
SRCS	:=	$(addprefix $(SRC_DIR)/,$(ERRORS_PATH))		\
			$(SRC_PATH)	

#Object ########################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
DEPS		:=	$(OBJ_FILES:.o=.d)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))


DEPENDENCIES	:= $(addprefix $(OBJ_DIR)/,$(DEPS))

# Rules ########################################################################
.PHONY: all fsa val tag clean fclean re d norm test ask_libft ask_libs

all: $(LIBFT_A) $(OBJ_DIR) $(NAME) Makefile libterm.a

$(LIBFT_A): FORCE
	@$(MAKE) -C $(LIBFT_DIR) -j >/dev/null

$(NAME): $(OBJS) $(INCLS) $(LIBS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

-include $(DEPENDENCIES)
$(OBJ_DIR)/%.o: %.c Makefile
	@$(CC) $(CFlAGS) $(INCL_CMD) -o $@ -c $<
	@echo Compiling $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

tag:
	@ctags -R .

clean: 
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

d: all
	$(OPT) ./a.out

FORCE:

norm:
	norminette $(SRCS)
	norminette $(INCLS)
