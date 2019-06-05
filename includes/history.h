#ifndef HISTORY_H
# define HISTORY_H

# define HIST_FILE "~/.42sh_history"
# define HIST_SIZE 500

# include "input.h"

typedef struct			s_hist_lst {
	char				*txt;
	char				*cpy;
	char				keep;
	struct s_hist_lst	*prev;
	struct s_hist_lst	*next;
}						t_hist_lst;


/*
**	Retrieving and writing history to/from a file
*/

t_hist_lst				*get_history(const char **env);
int						open_history(const char **env, int options);
int						write_to_history(t_st_cmd *st_cmd, const char **env);
int						get_next_line(const int fd, char **line);

/*
**	Utils for hist_lst structure : appending, creating, inserting etc...
*/

t_hist_lst				*insert_left(t_hist_lst *hist_lst, const char *line,
						char keep);
t_hist_lst				*insert_right(t_hist_lst *hist_lst, const char *line,
						char keep);
t_hist_lst				*create_hist_lst(const char *line, char keep);
void					print_hist_lst(t_hist_lst *hist_lst);
t_hist_lst				*get_end_lst(t_hist_lst *hist_lst);
t_hist_lst				*get_begin_lst(t_hist_lst *hist_lst);

/*
**	Getting previous history and next history and dislpaying it on screen
*/

void					get_previous_history(t_st_cmd *st_cmd);
void					get_next_history(t_st_cmd *st_cmd);

void					adjust_history(t_st_cmd *st_cmd, const char *line,
						int keep);
void					free_hist_lst(t_hist_lst *hist_lst);

void					switch_st_cmd(t_st_cmd *st_cmd, char *newcmd);
int						switch_and_return(char buf, t_st_cmd *st_cmd);

/*
**	Reverse Search History functions
*/

int						strstr_adapted(const char *haystack, const char *needle);
int						init_vars_rsh_and_prompt
							(t_st_cmd *st_cmd, size_t *malloc_size,
							 int *prompt_type, char **stock);
void					realloc_stock(char **stock, char buf, size_t *malloc_size);
int						is_quit_char(char buf);

#endif
