#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# define INIT_TXT_SIZE 2 // change to 32(?) later but for debug purpose it's 2
# define BUF_SIZE 4
# define STD_PROMPT "42sh $ "
# include "lexer.h"
# define MAX_DISPLAY 50
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

typedef struct				s_auto_comp
{
	unsigned int			len;
	unsigned int			rank;
	int						type;
	char					*name;
	struct s_auto_comp		*next;
	struct s_auto_comp		*prev;
}							t_auto_comp;

enum {REGULAR, DIRECTORY};

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

/*
**	auto_completion functions
*/

char						*new_auto_completion(char *input, unsigned int len);
char						*get_ret_or_display_matches(t_auto_comp *match, char *to_find, unsigned int len);
void						new_sort_list(t_auto_comp **match);
int							del_match_unique(t_auto_comp *match);
int							del_match(t_auto_comp *match);
int							get_cols_term(void);
int							get_columns_display(int count, int maxlen);
int							get_rows_display(int count, int cols);
int							create_match_link(t_auto_comp **match, char *str, unsigned char type);
int							compare_entry(char *s, char *n);
int							compare_entry2(char *s, char *n);
void						handler_is_display(int signo);
char						*get_to_find_file(char *s);
char						*get_path_file(char *s, char **find);
void						handler_is_display(int signo);
t_auto_comp					*ft_list_sort_ascii(t_auto_comp *lst);
t_auto_comp					*ft_lst_swap(t_auto_comp *file1, t_auto_comp *file2);
char						*lst_to_string_auto_c(t_list *lst);
int							lst_len_until_cursor_pos(t_list *lst);
char						*lst_to_string_auto_c(t_list *lst);
int							is_same_char(char a, char b);
int							find_matching_exe(char **path, t_auto_comp **match, char *to_find, int is_exe);

#endif
