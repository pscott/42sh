################################################################################
# Basics #######################################################################
NAME	:=	libft.a
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--leak-check=full --track-origins=yes --show-leak-kinds=all		\
				--show-reachable=no

SCRIPT_PATH	:= ../script

# Libraries	####################################################################
LIB_INCL	:=	
LIBFT_A		:=	
LIBTERM_A	:=	

LIBS		:= 

# Includes #####################################################################
INCL_DIRS	:=	includes
INCL_CMD	:=	$(addprefix -I,$(INCL_DIRS))

INCL_FILES	:=	libft.h ft_printf.h

INCLS		:=	$(addprefix includes/,$(INCL_FILES))



# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	STD_FUNC_DIR		:= std_func
	CONVERSION_DIR		:= conversion
	FORMATS_DIR			:= formats
	FT_ITOA_DIR			:= ft_itoa
	GET_LEN_DIR			:= get_len
	HELPERS_DIR			:= helpers
	INCREMENTERS_DIR	:= incrementers
	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(STD_FUNC_DIR) $(CONVERSION_DIR) $(FORMATS_DIR)			\
					$(FT_ITOA_DIR) $(GET_LEN_DIR) $(HELPERS_DIR)				\
					$(INCREMENTERS_DIR)

#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	ft_printf.c getters.c isprint_special.c parse_struct.c			\
				set_data_len.c spec_init.c wildcard.c
	#srcs subfiles names
	STD_FUNC_FILES		:=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c	\
							ft_isascii.c ft_isdigit.c ft_isprint.c ft_lstadd.c	\
							ft_lstappend.c ft_memmove.c ft_lstmap.c				\
							ft_lstdel.c ft_lstdelone.c ft_lstiter.c				\
							ft_lstnew.c ft_lstrmdup.c ft_lstsort.c				\
							ft_memalloc.c ft_memccpy.c ft_lstlen.c				\
							ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c		\
							ft_memset.c ft_putchar.c ft_putchar_fd.c			\
							ft_putendl.c ft_putendl_fd.c ft_strdel.c			\
							ft_putnbr.c ft_putnbr_fd.c ft_putstr.c				\
							ft_putstr_fd.c ft_strcat.c ft_strjoin.c				\
							ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c		\
							ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c	\
							ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c	\
							ft_strncat.c ft_strnstr.c ft_strsub.c				\
							ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c	\
							ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c	\
							ft_strtrim.c ft_tolower.c ft_toupper.c ft_itoa.c	\
							ft_putchar_err.c ft_free_ntab.c ft_realloc.c		\
							ft_dup_ntab.c ft_ntab_len.c ft_strndup.c \
							ft_print_ntab.c
	CONVERSION_FILES	:=	conv_helper.c converters.c
	FORMATS_FILES		:=	format_int.c format_char.c format_unsigned.c		\
							format_string.c format_conv.c format_p.c			\
							format_float.c
	FT_ITOA_FILES		:=	ft_nitoa.c ft_litoa.c ft_llitoa.c ft_hitoa.c		\
							ft_hhitoa.c ft_uitoa.c
	GET_LEN_FILES		:=	get_len.c get_ulen.c
	HELPERS_FILES		:=	ft_atoi_move.c null_data.c ft_special_memset.c		\
							utils.c values.c unsigned_helper.c choose_value.c	\
							float_helper.c ft_strncat_move.c
	INCREMENTERS_FILES	:=	increm_format.c increm_string.c 

#list of all .c files
C_FILES	:=	$(SRC_FILES) $(STD_FUNC_FILES) $(CONVERSION_FILES) $(FORMATS_FILES)		\
			$(FT_ITOA_FILES) $(GET_LEN_FILES) $(HELPERS_FILES) $(INCREMENTERS_FILES)
			

# Complete path of each .c files ###############################################
SRC_PATH			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
STD_FUNC_PATH		:=	$(addprefix $(STD_FUNC_DIR)/,$(STD_FUNC_FILES))
CONVERSION_PATH		:=	$(addprefix $(CONVERSION_DIR)/,$(CONVERSION_FILES))
FORMATS_PATH		:=	$(addprefix $(FORMATS_DIR)/,$(FORMATS_FILES))
FT_ITOA_PATH		:=	$(addprefix $(FT_ITOA_DIR)/,$(FT_ITOA_FILES))
GET_LEN_PATH		:=	$(addprefix $(GET_LEN_DIR)/,$(GET_LEN_FILES))
HELPERS_PATH		:=	$(addprefix $(HELPERS_DIR)/,$(HELPERS_FILES))
INCREMENTERS_PATH	:=	$(addprefix $(INCREMENTERS_DIR)/,$(INCREMENTERS_FILES))

#list of all "path/*.c"
SRCS	:=	$(addprefix $(SRC_DIR)/,$(STD_FUNC_PATH))		\
			$(addprefix $(SRC_DIR)/,$(CONVERSION_PATH))		\
			$(addprefix $(SRC_DIR)/,$(FORMATS_PATH))		\
			$(addprefix $(SRC_DIR)/,$(FT_ITOA_PATH))		\
			$(addprefix $(SRC_DIR)/,$(GET_LEN_PATH))		\
			$(addprefix $(SRC_DIR)/,$(HELPERS_PATH))		\
			$(addprefix $(SRC_DIR)/,$(INCREMENTERS_PATH))	\
			$(SRC_PATH)

#Object ########################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test

all: $(NAME) Makefile libft.a

fsa: $(SRCS)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)

val: $(SRCS)
	$(CC) $(DEBUG_FLAG) $(INCL_CMD) $(LIB_INCL) $^ -o $(NAME)

rmh:
	$(SCRIPT_PATH)/42header_c_rm.sh $(SRCS) $(INCLS)

adh: rmh
	vim -ns $(SCRIPT_PATH)/42header_add.keys $(SRCS) $(INCLS)

$(NAME): $(OBJS) $(INCLS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFlAGS) $(INCL_CMD) -o $@ -c $<
	@echo Compiling $@

tag:
	@ctags -R .

clean: 
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

d: all
	$(OPT) ./$(NAME)

norm: adh
	norminette $(SRCS)
	norminette $(INCLS)
