#ifndef HISTORY_H
# define HISTORY_H

# include "input.h"

# define HIST_FILE "~/.21sh_history"
# define HIST_SIZE 500

typedef struct			s_hist_lst
{
	struct s_hist_lst	*prev;
	char				*txt;
	struct s_hist_lst	*next;
	char				*cpy;
	char				keep;
}						t_hist_lst;

typedef struct			s_st_fc
{
	char				flags[4];
	char				*first;
	char				*last;
}						t_st_fc;

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
**	Getting previous history and next history and displaying it on screen
*/

void					get_previous_history(t_st_cmd *st_cmd);
void					get_next_history(t_st_cmd *st_cmd);

void					adjust_history(t_st_cmd *st_cmd, int keep);
void					free_hist_lst(t_hist_lst *hist_lst);

void					switch_st_cmd(t_st_cmd *st_cmd, char *newcmd);
int						switch_and_return(t_st_cmd *st_cmd, char buf,
		char escape[BUF_SIZE + 1], int mode);
int						print_prompt_search_history(t_st_cmd *st_cmd);

/*
**	Reverse Search History functions
*/

int						strstr_adapted(const char *haystack,
							const char *needle);
int						init_vars_rsh_and_prompt(t_st_cmd *st_cmd,
							size_t *malloc_size,
							int *prompt_type, char **stock);
void					realloc_stock(char **stock, char buf,
							size_t *malloc_size);
int						is_quit_char(char buf);
int						check_exit_and_realloc(size_t *malloc_size,
							char buf, char escape[BUF_SIZE + 1],
							char **stock);
int						handle_quitting_chars_and_bcksp(char buf,
							char **stock);

#endif
