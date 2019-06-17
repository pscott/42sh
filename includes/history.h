#ifndef HISTORY_H
# define HISTORY_H

# include "input.h"

# define HIST_FILE "~/.21sh_history"
# define HIST_SIZE 32767

enum {edit, substitute};//norme no typedef?

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
	char				flag[4];
	char				*first;
	int					i_first;
	char				*last;
	int					i_last;
	char				*old_pattern;
	char				*new_pattern;
	char				*editor;
}						t_st_fc;

typedef enum			e_fc_error
{
	invalid_option = 1,
	invalid_mix,
	editor_unspecified,
	path_unspecified,
	cmd_not_found,
	no_cmd_found,
	out_of_range
}						t_fc_error;
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
int						get_hist_len(t_hist_lst *hist_lst);
t_hist_lst				*get_entry_lst(t_hist_lst *hist_lst, int index);
t_hist_lst				*get_entry_lst_word(t_hist_lst *hist_lst, char *word);

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

/*
**	FC functions
*/

/*
**			*	Lexing, parsing and utils functions
*/

int						init_st_fc(t_st_cmd *st_cmd, t_st_fc *st_fc, char **argv);
int						parse_editor_fc(char **argv, int i);
int						parse_case_s_fc(t_st_fc *st_fc, char **argv, int i);
int						get_first_and_last(t_st_fc *st_fc, char **argv, int i);
int						error_fc(char *s, int i, int type, t_st_fc *st_fc);
int						error_fc_histo(char *s, int i, int type, t_st_fc *st_fc);
int						error_fc_index(char *flag);
int						is_valid_mix(char flag[4], char c);
int						is_valid_option(char *s, int i);

/*
**			*	Actual executing functions
*/

char					*fc_s_yes_old_yes_new(t_st_fc *st_fc, char *hist_curr,
							int old_cmd_len);
char					*fc_s_yes_old_no_new(t_st_fc *st_fc, char *hist_curr,
							int old_cmd_len);
char					*fc_s_no_old_yes_new(t_st_fc *st_fc,
							int old_cmd_len);
int						fc_execute_cmd(t_st_cmd *st_cmd, char *file, int type);
int						fc_edit_open_editor(t_st_cmd *st_cmd, t_st_fc *st_fc,
							char **tmp_file, int tmp_file_fd);
int						fc_edit_open_file(t_st_cmd *st_cmd, t_st_fc *st_fc,
							char **tmp_file);
int						fc_display_reverse(t_st_cmd *st_cmd, t_st_fc *st_fc);


#endif
