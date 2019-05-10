#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# define INIT_TXT_SIZE 2 // change to 32(?) later but for debug purpose it's 2
# define BUF_SIZE 4
# define STD_PROMPT "psh $ "
# include "lexer.h"

typedef struct				s_st_txt {
	char					*txt;
	size_t					malloc_size;
	size_t					data_size;
	size_t					tracker;
}							t_st_txt;

typedef struct				s_st_prompt {
	char					*prompt;
	size_t					size;
}							t_st_prompt;

typedef struct				s_st_cmd {
	struct s_st_txt			*st_txt;
	t_pos					start_pos;
	t_pos					relative_pos;
	struct winsize			window;
	struct s_st_prompt		*st_prompt;
	struct s_hist_lst		*hist_lst;
	struct s_st_cmd			*next;
	struct s_st_cmd			*prev;
}							t_st_cmd;

# include "history.h"
/*
**	st_txt functions
*/

t_st_txt					*init_st_txt(const char *txt);

/*
**	st_prompt functions
*/

t_st_prompt					*init_st_prompt(const char *prompt);

/*
**	st_cmd functions
*/

t_st_cmd					*get_first_st_cmd(t_st_cmd *st_cmd);
t_st_cmd					*get_last_st_cmd(t_st_cmd *st_cmd);
t_st_cmd					*get_st_cmd(t_st_cmd **new_struct);
t_st_cmd					*init_st_cmd(const char **env);
t_st_cmd					*append_st_cmd(t_st_cmd *st_cmd, const char *txt,
		const char *prompt);
t_st_cmd					*reset_st_cmd(t_st_cmd *old_st_cmd);
void						update_window_struct(struct winsize *window);
void						init_relative_pos(t_st_cmd *st_cmd);

int							write_line(t_st_cmd *st_cmd);
void						write_st_cmd(t_st_cmd *st_cmd);
void						write_from_start(t_st_cmd *st_cmd);
void						update_start_pos(t_st_cmd *st_cmd);
void						get_pos(t_st_cmd *st_cmd, size_t tracker);
void						go_back_to_start(t_st_cmd *st_cmd);
#endif
