#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# include "line_editing.h"
# include "history.h"


/*
**	Input checking
*/

int				check_for_arrows(t_st_cmd *st_cmd, const char *buf);
int				check_for_quit(const char *buf);
int				check_for_enter(const char *buf);
int				check_for_signal(const char *buf);
int				check_for_delete(t_st_cmd *st_cmd, char *buf);

/*
**	Arrow movement
*/

void			move_arrow_left(t_st_cmd *st_cmd);
void			move_arrow_right(t_st_cmd *st_cmd);
void			go_to_start(t_st_cmd *st_cmd);
void			go_to_end(t_st_cmd *st_cmd);


/*
**	Backspace and delete functions
*/

void			delete_right(t_st_cmd *st_cmd);
void			delete_left(t_st_cmd *st_cmd);

/*
** Read input
*/

int				input_loop(t_st_cmd *st_cmd);

/*
** General display
*/

void			reposition_cursor(t_st_cmd *st_cmd);
void			print_prompt(t_st_prompt *st_prompt);
void			signal_setup(void);
void			reset_dfl(void);
void			reset_ign(void);

/*
**	Input string manipulation
*/

size_t			ft_printable_len(const char *str);
void			insert_str(t_st_cmd *st_cmd, const char *buf,
		size_t printable_len);


void			clean_exit(int exitno);
/*
**	Functions that have to do with setting up st_cmd
*/

t_st_cmd	*get_st_cmd(t_st_cmd **new_struct);
t_st_cmd	*init_st_cmd(const char **env);

void			sigint_handler(int signo);
char			*concatenate_txt(t_st_cmd *st_cmd);
#endif
