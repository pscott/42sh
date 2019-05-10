################################################################################
# Basics #######################################################################
NAME	:=	21sh
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--track-origins=yes --show-leak-kinds=all --track-fds=yes \
				--show-reachable=no

# Libraries ####################################################################
LIBFT_DIR		:=	libft
LIBTERM_DIR		:=	libterm

LIB_INCL		:=	-L $(LIBFT_DIR) -lft -L $(LIBTERM_DIR) -lterm -ltermcap

LIBFT_A			:=	$(addprefix $(LIBFT_DIR)/,libft.a)
LIBTERM_A		:=	$(addprefix $(LIBTERM_DIR)/,libterm.a)

LIBS			:= $(LIBFT_A) $(LIBTERM_A)

# Includes #####################################################################
INCL_DIR	:=	includes libft/includes libterm/includes
INCL_CMD	:=	$(addprefix -I,$(INCL_DIR))

INCL_FILES	:=	tosh.h lexer.h ast.h reader.h history.h get_next_line.h line_editing.h builtins.h errors.h

INCLS		:=	$(addprefix includes/,$(INCL_FILES))

# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	ENV_DIR				:=	environment
	ERRORS_DIR			:=	errors
	LEXER_DIR			:=	lexer
	PARSER_DIR			:=	token_parser
	PIPELINE_DIR		:=	pipeline
	READER_DIR			:=	reader
	EXPANDS_DIR			:=	expands
	HISTORY_DIR			:=	history
	SIGNALS_DIR			:=	signals
	L_E_DIR				:=	line_editing
	BUILTINS_DIR		:=	builtins
	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(ENV_DIR) $(ERRORS_DIR) $(LEXER_DIR) $(PARSER_DIR) \
					$(PIPELINE_DIR) $(READER_DIR) $(HISTORY_DIR) $(EXPANDS_DIR) \
				   	$(SIGNALS_DIR) $(L_E_DIR) $(BUILTINS_DIR)


#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	handle_input.c free.c main.c \
	#srcs subfiles names
	ENV_FILES		:=	environ_set.c environ_utils.c init_env.c shlvl.c
	ERRORS_FILES	:=	errors.c print_errors.c error_exit.c
	LEXER_FILES		:=	lexer.c lexer_tools.c lexer_op_chart.c get_token.c\
						lexer_debug.c
	PARSER_FILES	:=	token_parser.c token_parser_utils.c
	PIPELINE_FILES	:=	parse_pipeline.c parse_redirections.c \
						execute_commands.c \
						redir_great.c redir_dgreat.c redir_less.c redir_dless.c \
						check_token_type.c redir_fd_great.c
	READER_FILES	:=	arrows.c check_commands.c clean_exit.c prompt.c \
						input_loop.c cursor_position.c input_utils.c \
						delete.c txt_cat.c
	EXPANDS_FILES	:=	parse_expands.c parse_dollars.c parse_tildes.c \
						parse_quotes.c 
	HISTORY_FILES	:=	hist_file.c get_next_line.c hist_lst.c switch_history.c
	SIGNALS_FILES	:=	signals.c
	L_E_FILES		:=	st_cmd.c st_prompt.c st_txt.c writing.c
	BUILTINS_FILES	:=	cmd_cd.c builtins_cmd.c


#list of all .c files
C_FILES	:=	$(SRC_FILES) $(ENV_FILES) $(ERRORS_FILES) $(LEXER_FILES)\
			$(PARSER_FILES) $(PIPELINE_FILES) $(READER_FILES) $(HISTORY_FILES) \
			$(EXPANDS_FILES) $(SIGNALS_FILES) $(L_E_FILES) $(BUILTINS_FILES)


# Complete path of each .c files ###############################################
SRC_PATH			:=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))
ENV_PATH			:=	$(addprefix $(ENV_DIR)/,$(ENV_FILES))
ERRORS_PATH			:=	$(addprefix $(ERRORS_DIR)/,$(ERRORS_FILES))
LEXER_PATH			:=	$(addprefix $(LEXER_DIR)/,$(LEXER_FILES))
PARSER_PATH			:=	$(addprefix $(PARSER_DIR)/,$(PARSER_FILES))
PIPELINE_PATH		:=	$(addprefix $(PIPELINE_DIR)/,$(PIPELINE_FILES))
READER_PATH			:=	$(addprefix $(READER_DIR)/,$(READER_FILES))
EXPANDS_PATH		:=	$(addprefix $(EXPANDS_DIR)/,$(EXPANDS_FILES))
HISTORY_PATH		:=	$(addprefix $(HISTORY_DIR)/,$(HISTORY_FILES))
SIGNALS_PATH		:=	$(addprefix $(SIGNALS_DIR)/,$(SIGNALS_FILES))
L_E_PATH			:=	$(addprefix $(L_E_DIR)/,$(L_E_FILES))
BUILTINS_PATH		:=	$(addprefix $(BUILTINS_DIR)/,$(BUILTINS_FILES))

#list of all "path/*.c"
SRCS	:=	$(addprefix $(SRC_DIR)/,$(ENV_PATH)) \
			$(addprefix $(SRC_DIR)/,$(ERRORS_PATH)) \
			$(addprefix $(SRC_DIR)/,$(LEXER_PATH)) \
			$(addprefix $(SRC_DIR)/,$(PARSER_PATH)) \
			$(addprefix $(SRC_DIR)/,$(PIPELINE_PATH)) \
			$(addprefix $(SRC_DIR)/,$(READER_PATH)) \
			$(addprefix $(SRC_DIR)/,$(EXPANDS_PATH)) \
			$(addprefix $(SRC_DIR)/,$(HISTORY_PATH)) \
			$(addprefix $(SRC_DIR)/,$(SIGNALS_PATH)) \
			$(addprefix $(SRC_DIR)/,$(L_E_PATH)) \
			$(addprefix $(SRC_DIR)/,$(BUILTINS_PATH)) \
			$(SRC_PATH)

#Object ########################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test ask_libft \
	

all: Makefile ask_libs $(NAME)

ask_libs: ask_libft ask_libterm

ask_libft:
	@$(MAKE) -qC libft ; if [ $$? != "0" ] ; then\
		$(MAKE) -j -C libft;\
		fi

ask_libterm:
	@$(MAKE) -qC libterm child; if [ $$? != "0" ] ; then\
		$(MAKE) -j -C libterm;\
		fi

$(LIBS): ask_libs

fsa: $(SRCS) $(LIBS)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)
	$(OPT) ./$(NAME)

val: $(SRCS) $(LIBS)
	$(CC) $(DEBUG_FLAG) $(INCL_CMD) $(LIB_INCL) $^ -o $(NAME)
	valgrind $(VAL_FLAGS) $(OPT) ./$(NAME)

rmh:
	./script/42header_c_rm.sh $(SRCS) $(INCLS)

adh: rmh
	vim -ns script/42header_add.keys $(SRCS) $(INCLS)

$(NAME): $(OBJS) libft/libft.a libterm/libterm.a
	$(CC) $(CFLAGS) $(INCL_CMD) $^ -o $@ $(LIB_INCL)

$(OBJ_DIR)/%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	$(CC) $(CFlAGS) $(INCL_CMD) -o $@ -c $<
	echo Compiling $@

tags:
	ctags -R .

clean: 
	$(MAKE) clean -C libft
	$(MAKE) clean -C libterm
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C libterm
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

re: fclean all

d: all
	$(OPT) ./$(NAME)


norm: adh
	norminette $(SRCS)
	norminette $(INCLS)
