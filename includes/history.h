#ifndef HISTORY_H
# define HISTORY_H

# include "reader.h"
# define HIST_FILE "~/.21sh_history"
# define HIST_SIZE 500

typedef struct		s_hist_lst {
	char				*txt;
	char				*cpy;
	char				keep;
	struct s_hist_lst *prev;
	struct s_hist_lst *next;
}					t_hist_lst;

t_hist_lst	*get_history(const char **env);
int			write_to_history(t_st_cmd *st_cmd, const char **env);

/*
**	Utils for hist_lst structure : appending, creating, inserting etc...
*/

t_hist_lst	*insert_left(t_hist_lst *hist_lst, char *line, char keep);
t_hist_lst	*insert_right(t_hist_lst *hist_lst, char *line, char keep);
t_hist_lst	*create_hist_lst(char *line, char keep);
void		print_hist_lst(t_hist_lst *hist_lst);
t_hist_lst	*get_end_lst(t_hist_lst *hist_lst);
t_hist_lst	*get_begin_lst(t_hist_lst *hist_lst);

/*
**	Getting previous history and next history and dislpaying it on screen
*/

void		get_previous_history(t_st_cmd *st_cmd);
void		get_next_history(t_st_cmd *st_cmd);



#endif
