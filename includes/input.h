#ifndef INPUT_H
# define INPUT_H

# include "ftsh.h"
# include "libterm.h"

/*
**	INIT_TXT_SIE : for debug it's 2, but maybe change it to 32 later
*/

# define INIT_TXT_SIZE 2
# define BUF_SIZE 4
# define STD_PROMPT "42sh $ "
# define PROMPT_REVERSE_I_SEARCH_SUCC "(reverse-i-search)"
# define PROMPT_REVERSE_I_SEARCH_FAIL "(failed reverse-i-search)"

typedef enum	e_input
{
	input_break,
	input_continue,
	input_stop
}				t_input;

typedef enum	e_search_case
{
	enter_case = 1,
	ctrl_c_case,
	quit_case
}				t_search_case;

typedef enum	e_input_mode
{
	regular,
	heredoc
}				t_input_mode;;

typedef struct			s_st_txt {
	char				*txt;
	size_t				malloc_size;
	size_t				data_size;
	size_t				tracker;
}						t_st_txt;

typedef struct			s_st_prompt {
	char				*prompt;
	size_t				size;
}						t_st_prompt;

typedef struct			s_st_cmd {
	struct s_st_txt		*st_txt;
	t_pos				start_pos;
	t_pos				relative_pos;
	struct winsize		*window;
	struct s_st_prompt	*st_prompt;
	struct s_hist_lst	*hist_lst;
	struct s_st_cmd		*next;
	struct s_st_cmd		*prev;
}						t_st_cmd;

int						handle_reverse_search_history(t_st_cmd *st_cmd,
						size_t malloc_size, int prompt_size);

/*
** Handling input
*/

int						is_valid_escape(char *str);
t_bool					handle_input(t_st_cmd *st_cmd, t_vars *vars);

/*
**	Input checking
*/

int						checkers(t_st_cmd *st_cmd, t_vars *vars, char *buf,
						int mode);
int						check_for_arrows(t_st_cmd *st_cmd, const char *buf);
int						check_for_quit(t_st_cmd *st_cmd, const char *buf);
int						check_for_enter(const char *buf);
int						check_for_signal(const char *buf);
int						check_for_delete(t_st_cmd *st_cmd, char *buf);
int						check_for_search_histo(t_st_cmd *st_cmd,
						const char *buf_received);
int						check_for_tab(t_st_cmd *st_cmd, const char *buf,
						t_vars *vars, int mode);
int						check_for_words(t_st_cmd *st_cmd, const char *buf);
char					*auto_completion(char *input, unsigned int len,
						t_vars *vars);
char					*auto_completion_hdoc(char *input,
						unsigned int len);

/*
**	Arrow movement
*/

void					move_arrow_left(t_st_cmd *st_cmd);
void					move_arrow_right(t_st_cmd *st_cmd);
void					go_to_start(t_st_cmd *st_cmd);
void					go_to_end(t_st_cmd *st_cmd);

/*
**	Backspace and delete functions
*/

void					delete_right(t_st_cmd *st_cmd);
void					delete_left(t_st_cmd *st_cmd);

/*
**	Jump words
*/

int						jump_words(t_st_cmd *st_cmd, int num);

/*
** Read input
*/

int						input_loop(t_st_cmd *st_cmd, t_vars *vars, int mode);

/*
**	Input string manipulation
*/

size_t					ft_printable_len(const char *str);
char					*ft_strdup_print(const char *str);
void					insert_str(t_st_cmd *st_cmd, const char *buf,
						size_t printable_len);

/*
**	st_txt functions
*/

t_st_txt				*init_st_txt(const char *txt);
void					free_st_txt(t_st_txt **st_txt);

/*
**	st_prompt functions
*/

t_st_prompt				*init_st_prompt(const char *prompt);
void					print_prompt(t_st_cmd *st_cmd);
void					print_prompt_search_histo(t_st_cmd *st_cmd,
						const char *buf, int prompt_type);
void					free_st_prompt(t_st_prompt **st_prompt);

/*
**	st_cmd functions
*/

t_st_cmd				*get_first_st_cmd(t_st_cmd *st_cmd);
t_st_cmd				*get_last_st_cmd(t_st_cmd *st_cmd);
t_st_cmd				*get_st_cmd(t_st_cmd **new_struct);
t_st_cmd				*init_st_cmd(const char **env);
t_st_cmd				*append_st_cmd(t_st_cmd *st_cmd, const char *txt,
						const char *prompt);
t_st_cmd				*reset_st_cmd(t_st_cmd *old_st_cmd);
t_st_cmd				*get_st_cmd(t_st_cmd **new_struct);
t_st_cmd				*init_st_cmd(const char **env);
char					*concatenate_txt(t_st_cmd *st_cmd);
void					free_st_cmd(t_st_cmd *st_cmd);
void					free_all_st_cmds(t_st_cmd **st_cmd);

#endif
