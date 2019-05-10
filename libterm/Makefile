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

SCRIPT_PATH	:= ../script

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
SRC_FILES	:=	cursor.c execute_cap.c print_line.c termcap_settings.c \
	#srcs subfiles names
	ERRORS_FILES	:=	error_attr.c error_caps.c error_getenv.c \
						error_getstr.c error_isatty.c error_tgetent.c \
						error_tgoto.c

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
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test ask_libft ask_libs

all: ask_libs $(NAME) Makefile libterm.a

ask_libs: ask_libft

child: $(NAME) tag Makefile

ask_libft:
	@$(MAKE) -qC $(LIBFT_DIR) ; if [ $$? != "0" ] ; then\
		$(MAKE) -j -C $(LIBFT_DIR) ;\
		fi

fsa: $(SRCS) $(LIBS)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)
	$(OPT) ./$(NAME)

val: $(SRCS) $(LIBS)
	$(CC) $(DEBUG_FLAG) $(INCL_CMD) $(LIB_INCL) $^ -o $(NAME)
	valgrind $(VAL_FLAGS) $(OPT) ./$(NAME)

rmh:
	$(SCRIPT_PATH)/42header_c_rm.sh $(SRCS) $(INCLS)

adh: rmh
	vim -ns $(SCRIPT_PATH)/42header_add.keys $(SRCS) $(INCLS)

$(NAME): $(OBJS) $(INCLS) $(LIBS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFlAGS) $(INCL_CMD) -o $@ -c $<
	@echo Compiling $@

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

norm: adh
	norminette $(SRCS)
	norminette $(INCLS)
