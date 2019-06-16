################################################################################

# Basics #######################################################################
NAME	:=	21sh
OPT		:=	
CC		:=	gcc
CFLAGS	:=	-Wall -Wextra #-Werror
MMD		:=	-MMD

DEBUG_FLAG	:=	-g
FSA_FLAGS	:=	$(DEBUG_FLAG) -fsanitize=address
VAL_FLAGS	:=	--track-origins=yes --show-leak-kinds=all --track-fds=yes \
				--show-reachable=no --leak-check=full

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

INCL_FILES	:=	ftsh.h lexer.h ast.h auto_completion.h input.h history.h \
				structures.h \
				line_editing.h builtins.h errors.h cmd_parsing.h execution.h \
				signals.h hashmap.h heredoc.h exp_arith.h env.h

INCLS		:=	$(addprefix includes/,$(INCL_FILES))


# Directories ##################################################################
SRC_DIR	:=	srcs
	#srcs subdirectories names
	ENV_DIR				:=	environment
	ERRORS_DIR			:=	errors
	LEXER_DIR			:=	lexer
	PARSER_DIR			:=	ast
	PIPELINE_DIR		:=	pipeline
	READER_DIR			:=	reader
	EXPANDS_DIR			:=	expands
	HISTORY_DIR			:=	history
	SIGNALS_DIR			:=	signals
	LINE_EDIT_DIR		:=	line_editing
	BUILTINS_DIR		:=	builtins
	AUTO_COMP_DIR		:=	auto_completion
	REDIR_DIR			:=	redirections
	EXEC_DIR			:=	execution
	HASHMAP_DIR			:=	hashmap
	EXP_ARITH_DIR		:=	exp_arith
	HEREDOC_DIR			:=	heredoc
	TMP_VAR_DIR			:=	variables_revamp

	#list of all srcs subdirectories
	SRC_SUBDIRS	:=	$(ENV_DIR) $(ERRORS_DIR) $(LEXER_DIR) $(PARSER_DIR) \
					$(PIPELINE_DIR) $(READER_DIR) $(HISTORY_DIR) \
					$(EXPANDS_DIR) $(SIGNALS_DIR) $(LINE_EDIT_DIR) \
					$(BUILTINS_DIR) $(REDIR_DIR) $(EXEC_DIR) $(AUTO_COMP_DIR) \
					$(EXP_ARITH_DIR) $(HEREDOC_DIR) $(TMP_VAR_DIR) \
					$(addprefix $(BUILTINS_DIR)/,$(HASHMAP_DIR))


#VPATH specifies a list of directories that 'make' should search
VPATH	:=	$(SRC_DIR) $(addprefix $(SRC_DIR)/,$(SRC_SUBDIRS))

# Srcs file names ##############################################################
SRC_FILES	:=	handle_input.c free.c main.c clean_exit.c introduction.c
	ENV_FILES		:=	environ_set.c environ_utils.c init_env.c shlvl.c\
						environ_unset.c
	ERRORS_FILES	:=	errors.c print_errors.c error_exit.c
	LEXER_FILES		:=	lexer.c lexer_tools.c lexer_op_chart.c get_token.c \
						copy_token_list.c lexer_escape_tools.c \
						check_special_token.c
	PARSER_FILES	:=	ast.c ast_utils.c
	PIPELINE_FILES	:=	parse_pipeline.c check_token_type.c
	READER_FILES	:=	check_sig_del_arrow.c prompt.c \
						input_loop.c input_utils.c \
						check_enter_quit_hist.c  txt_cat.c \
						checkers.c check_words.c check_tab.c \
						check_copy_paste.c
	EXPANDS_FILES	:=	parse_expands.c parse_tildes.c parse_vars.c \
						parse_quotes.c parse_arith_exp.c special_lltoa.c \
						substitute_utils.c parse_tildes_utils.c get_var_name.c
	HISTORY_FILES	:=	hist_file.c get_next_line.c  hist_lst_utils.c \
						getters.c switch_history.c insertion.c \
						handle_input_hist.c reverse_search_history.c \
						return_search_history.c write_history.c \
						reverse_search_history_utils.c
	SIGNALS_FILES	:=	signals_handlers.c signals_setup.c
	LINE_EDIT_FILES	:=	st_cmd_editing.c st_prompt.c st_txt.c writing.c \
						t_vars.c st_cmd_getters.c cursor_position.c \
						st_cmd_windows_struct_utils.c \
						reposition_cursor.c \
						jump_words.c delete.c arrows.c go_up.c go_down.c
	BUILTINS_FILES	:=	cmd_cd.c builtins_cmd.c cmd_hash.c cmd_exit.c \
						cmd_type.c cmd_setenv.c cmd_unsetenv.c cmd_echo.c \
						cmd_exit_utils.c cmd_cd_utils.c cmd_env.c \
						cmd_env_check.c cmd_set.c cmd_unset.c cmd_export.c
	REDIR_FILES		:=	redir_dgreat.c redir_fd_great.c fd_utils.c \
						redir_great.c redir_less.c parse_redirections.c \
						redir_fd_less.c redirections_errors.c redir_fd_utils.c \
						close_open_fds.c
	EXEC_FILES		:=	cmd_path.c execute_commands.c token_to_argv.c \
						execute_no_pipe_builtin.c exit_status.c
	AUTO_COMP_FILES	:=	auto_completion.c auto_completion_x_arg.c \
						bin_first_arg.c compare_entry.c \
						create_match_link.c del_match.c \
						dirs_and_exe_first_arg.c dirs_first_arg.c \
						display_auto_comp.c get_exe_names.c \
						get_next_line_a_c.c get_path_file.c \
						home_dirs_first_arg.c space_first_arg.c tilde_users.c \
						utils.c	utils2.c utils_display.c \
						auto_completion_spe.c \
						get_all_match.c formating_ret.c
	HASHMAP_FILES	:=	find_next_prime.c hash_main.c hashfun.c hashmap.c \
						hashmap_alloc.c hashmap_delete.c hashmap_print.c \
						get_hash_args.c hashmap_errors.c
	EXP_ARITH_FILES	:=	build_list.c check_errors.c create_op_link.c \
						exec_op_list.c exec_op_list_2.c exec_op_list_3.c \
						expansion_arith.c free_list.c array_utils.c \
						free_tokens.c ft_atoll.c ft_lltoa.c get_op_token.c \
						is_oper.c op_tokenizer.c op_tokenizer_clean.c \
						op_tokenizer_clean_2.c op_tokenizer_dirty.c \
						op_tokenizer_utils.c put_op_link.c ft_isempty.c
	HEREDOC_FILES	:=	heredoc.c heredoc_utils.c get_doc.c save_heredoc.c \
						clean_heredoc.c
	TMP_VAR_FILES	:=	set_default_shell_vars.c variables_utils.c \
						ntab_utils.c

#list of all .c files
C_FILES	:=	$(SRC_FILES) $(ENV_FILES) $(ERRORS_FILES) $(LEXER_FILES) \
			$(PARSER_FILES) $(PIPELINE_FILES) $(READER_FILES) \
			$(HISTORY_FILES) $(EXPANDS_FILES) $(SIGNALS_FILES) \
			$(LINE_EDIT_FILES) $(BUILTINS_FILES) $(REDIR_FILES) $(EXEC_FILES) \
			$(HASHMAP_FILES) $(AUTO_COMP_FILES) $(EXP_ARITH_FILES) \
			$(HEREDOC_FILES) $(TMP_VAR_FILES)

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
LINE_EDIT_PATH		:=	$(addprefix $(LINE_EDIT_DIR)/,$(LINE_EDIT_FILES))
BUILTINS_PATH		:=	$(addprefix $(BUILTINS_DIR)/,$(BUILTINS_FILES))
AUTO_COMP_PATH		:=	$(addprefix $(AUTO_COMP_DIR)/,$(AUTO_COMP_FILES))
REDIR_PATH			:=	$(addprefix $(REDIR_DIR)/,$(REDIR_FILES))
EXEC_PATH			:=	$(addprefix $(EXEC_DIR)/,$(EXEC_FILES))
EXP_ARITH_PATH		:=	$(addprefix $(EXP_ARITH_DIR)/,$(EXP_ARITH_FILES))
HASHMAP_PATH		:=	$(addprefix $(HASHMAP_DIR)/,$(HASHMAP_FILES))
#	builtin/ + hashmap/*.c
HASHMAP_PATH		:=	$(addprefix $(BUILTINS_DIR)/,$(HASHMAP_PATH))
HEREDOC_PATH		:=	$(addprefix $(HEREDOC_DIR)/,$(HEREDOC_FILES))
TMP_VAR_PATH		:=	$(addprefix $(TMP_VAR_DIR)/,$(TMP_VAR_FILES))


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
			$(addprefix $(SRC_DIR)/,$(LINE_EDIT_PATH)) \
			$(addprefix $(SRC_DIR)/,$(BUILTINS_PATH)) \
			$(addprefix $(SRC_DIR)/,$(AUTO_COMP_PATH)) \
			$(addprefix $(SRC_DIR)/,$(REDIR_PATH)) \
			$(addprefix $(SRC_DIR)/,$(EXEC_PATH)) \
			$(addprefix $(SRC_DIR)/,$(EXP_ARITH_PATH)) \
			$(addprefix $(SRC_DIR)/,$(HASHMAP_PATH)) \
			$(addprefix $(SRC_DIR)/,$(HEREDOC_PATH)) \
			$(addprefix $(SRC_DIR)/,$(TMP_VAR_PATH)) \
			$(SRC_PATH)

#Object ########################################################################
OBJ_DIR		:=	objs
OBJ_FILES	:=	$(C_FILES:.c=.o)
DEPS		:=	$(OBJ_FILES:.o=.d)
OBJS		:=	$(addprefix $(OBJ_DIR)/,$(OBJ_FILES))


DEPENDENCIES	:= $(addprefix $(OBJ_DIR)/,$(DEPS))


# Rules ########################################################################
.PHONY: all fsa val rmh adh tag clean fclean re d norm test ask_libft

all: $(LIBFT_A) $(LIBTERM_A) $(OBJ_DIR) $(NAME)

$(LIBFT_A): FORCE
	@make -C $(LIBFT_DIR)

$(LIBTERM_A): FORCE
	@make -C $(LIBTERM_DIR)

fsa: $(SRCS) $(LIBS) $(INCLS)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)
	$(OPT) ./$(NAME)

val: $(SRCS) $(LIBS) $(INCLS)
	$(CC) $(DEBUG_FLAG) $(INCL_CMD) $(LIB_INCL) $(SRCS) -o $(NAME)
	valgrind $(VAL_FLAGS) $(OPT) ./$(NAME)

rmh:
	./script/42header_c_rm.sh $(SRCS) $(INCLS)
	make -C $(LIBFT_DIR) rmh
	make -C $(LIBTERM_DIR) rmh

adh: rmh
	vim -ns script/42header_add.keys $(SRCS) $(INCLS)
	make -C $(LIBFT_DIR) adh
	make -C $(LIBTERM_DIR) adh

$(NAME): $(OBJS) libft/libft.a libterm/libterm.a
	$(CC) $(CFLAGS) $(INCL_CMD) $^ -o $@ $(LIB_INCL)

-include $(DEPENDENCIES)
$(OBJ_DIR)/%.o: %.c Makefile
	@echo Compiling $@
	@$(CC) $(CFLAGS) $(MMD) $(INCL_CMD) -o $@ -c $<

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

tags:
	ctags -R .

#print-%  : ; @echo $* = $($*)

clean: 
	$(MAKE) clean -C libft
	$(MAKE) clean -C libterm
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft
	$(MAKE) fclean -C libterm
	$(RM) $(NAME)
	$(RM) -r $(NAME).dSYM

FORCE:

re: fclean all

d: all
	@$(OPT) ./$(NAME)

norm:
	norminette $(SRCS) | grep -v -e "C++ comment" -e "42 header"\
		| grep -B 1 "Error"
	norminette $(INCLS) | grep -v -e "C++ comment" -e "42 header"\
		| grep -B 1 "Error"
