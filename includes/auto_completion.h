#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H

# define MAX_DISPLAY 80
# define PATH_MAX 4096
# define NAME_MAX 4096
# define BUFF_SIZE 256
# define MAX_FD 4864
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include "42sh.h"

typedef struct				s_auto_comp
{
	char					*name;
	struct s_auto_comp		*next;
	struct s_auto_comp		*prev;
}							t_auto_comp;

/*
**	General functions
*/
char						*auto_completion_bin(t_vars *vars,
								const char *str,
								const char *to_find_and_next_char);
char						*auto_completion_space(t_vars *vars);
char						*auto_completion_x_arg(const char *input,
								const char *to_find_and_next_char);
char						*home_directory_first_arg(const char *to_find);
char						*users_passwd(const char *to_find);
int							get_needed_values(const char *input,
								unsigned int len, char **str,
								char **to_find_full);

/*
**	Display functions
*/

char						*get_ret_or_display_matches(t_auto_comp *match,
								const char *to_find, unsigned int len);
void						handler_is_display(int signo);
void						print_spaces(const char *s, unsigned int cols);
int							is_display(unsigned int count);

/*
**	Creating list of matches functions
*/

int							create_match_link(t_auto_comp **match,
								char *str);
int							compare_entry(const char *s,
								const char *n);
int							compare_entry2(const char *s,
								const char *n);
int							get_path_file_and_to_find(const char *arg,
								char **path, char **to_find);
int							get_matching_exe(char **path, t_auto_comp **match,
								const char *to_find_real, const char *next);
char						*get_dirs_first_arg(const char *directory,
								const char *str, unsigned int len);

/*
**	Utils functions
*/

int							del_match(t_auto_comp *match);
unsigned int				get_cols_term(void);
unsigned int				get_columns_display(unsigned int count,
								unsigned int maxlen);
unsigned int				get_rows_display(unsigned int count,
								unsigned int cols);
void						*ft_lst_swap(t_auto_comp **l1,
								t_auto_comp **l2);
int							is_same_char(char a, char b);
int							get_path(char ***path, t_vars *vars);
void						get_pwd_and_pwd_slash(char **pwd,
								char **pwd_slash);
char						*rm_spaces_path(const char *str);
char						*search_dirs_and_exe(const char *str);
unsigned int				get_max_len(t_auto_comp *match);
unsigned int				len_lst(t_auto_comp *lst);
int							get_next_line_a_c(const int fd, char **line);
int							free_two_strings(char **s1, char **s2);
int							free_four_strings(char **s1, char **s2, char **s3,
								char **s4);
void						initialize_str(char **s1, char **s2, char **s3,
								char **s4);

#endif
