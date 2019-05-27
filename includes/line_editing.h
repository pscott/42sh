#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "42sh.h"
# include "input.h"
# define MAX_DISPLAY 2000
# define PATH_MAX 4096
# define NAME_MAX 4096
# define PROMPT_REVERSE_I_SEARCH_FAIL "(failed reverse-i-search)"
# define PROMPT_REVERSE_I_SEARCH_SUCC "(reverse-i-search)"
# include <dirent.h>
# include <sys/types.h>
# include <pwd.h>
# include <sys/stat.h> 


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
	char					*name;
	struct s_auto_comp		*next;
	struct s_auto_comp		*prev;
}							t_auto_comp;

char						*new_auto_completion(char *input, unsigned int len, t_vars *vars);
char						*get_ret_or_display_matches(t_auto_comp *match, const char *to_find, unsigned int len);
void						new_sort_list(t_auto_comp **match);
int							del_match_unique(t_auto_comp *match);
int							del_match(t_auto_comp *match);
unsigned int				get_cols_term(void);
unsigned int				get_columns_display(unsigned int count, unsigned int maxlen);
unsigned int				get_rows_display(unsigned int count, unsigned int cols);
int							create_match_link(t_auto_comp **match, char *str);
int							compare_entry(const char *s, const char *n);
int							compare_entry2(const char *s, const char *n);
void						handler_is_display(int signo);
char						*get_to_find_file(char *s);
int							get_path_file_and_to_find(const char *arg, char **path, char **to_find);
void						handler_is_display(int signo);
t_auto_comp					*ft_list_sort_ascii(t_auto_comp **lst);
t_auto_comp					*ft_lst_swap(t_auto_comp *file1, t_auto_comp *file2);
char						*lst_to_string_auto_c(t_list *lst);
int							lst_len_until_cursor_pos(t_list *lst);
char						*lst_to_string_auto_c(t_list *lst);
int							is_same_char(char a, char b);
int							find_matching_exe(char **path, t_auto_comp **match, const char *to_find_real, const char *next);
int							get_needed_values(const char *input, unsigned int len, char **str , char **to_find_full);
int							get_path(char ***path, t_vars *vars);
char						*rm_spaces_path(const char *str);
char						*new_auto_completion_space(t_vars *vars);
char						*search_dirs_first_arg(const char *directory, const char *str, unsigned int len);
char                       *new_auto_completion_bin(t_vars *vars, const char *str, const char *to_find_and_next_char);
int							new_auto_completion_file(char *str, unsigned int len);
char						*search_dirs_and_exe(const char *str);
char						*home_directory_first_arg(const char *to_find);
char						*tilde_no_slash(char *to_find, int len);
int							find_all_except_dots(const char *directory, t_auto_comp **match);
unsigned int				get_max_len(t_auto_comp *match);
unsigned int				len_lst(t_auto_comp *lst);
void						print_spaces(const char *s, unsigned int cols);
int							is_display(unsigned int count);
int							find_all_match(char *directory, t_auto_comp **match, const char *to_find, const char *next);
char						*handle_x_arg(const char *input, const char *to_find_and_next_char);
char						*users_passwd(const char *to_find);
int							get_next_line_2(const int fd, char **line);
int							free_two_strings(char **s1, char **s2);
int							free_four_strings(char **s1, char **s2, char **s3, char **s4);


#endif
