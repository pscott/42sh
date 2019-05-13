#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "42sh.h"
# include "input.h"
# define MAX_DISPLAY 50

/*
**	Window struct
*/
void						update_window_struct(struct winsize *window);

/*
**	On-screen position functions
*/

void						init_relative_pos(t_st_cmd *st_cmd);
void						update_start_pos(t_st_cmd *st_cmd);
void						get_pos(t_st_cmd *st_cmd, size_t tracker);
void						go_back_to_start(t_st_cmd *st_cmd);
void						reposition_cursor(t_st_cmd *st_cmd); // ? 


/*
**	Writing functions
*/
int							write_line(t_st_cmd *st_cmd);
void						write_st_cmd(t_st_cmd *st_cmd);
void						write_from_start(t_st_cmd *st_cmd);

/*
**	auto_completion functions
*/

enum						{DIRECTORY, REGULAR};
typedef struct				s_auto_comp
{
	unsigned int			len;
	unsigned int			rank;
	int						type;
	char					*name;
	struct s_auto_comp		*next;
	struct s_auto_comp		*prev;
}							t_auto_comp;

char						*new_auto_completion(char *input, unsigned int len, t_vars *vars);
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
