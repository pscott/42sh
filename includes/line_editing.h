#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "input.h"

/*
**	Window struct
*/

void					update_window_struct(struct winsize *window);
struct winsize			*init_window_struct(void);

/*
**	On-screen position functions
*/

void					increment_pos(char to_write, t_pos *cursor_pos,
	struct winsize *window);
void					init_relative_pos(t_pos *cursor_pos,
	struct winsize *window, size_t prompt_size);
t_st_cmd				*go_back_to_start(t_st_cmd *st_cmd);
void					go_to_prompt_start(t_st_cmd *st_cmd);
void					merge_pos(t_pos *new_pos, t_pos *old_pos);
void					reposition_cursor(t_st_cmd *st_cmd, size_t new_tracker);

/*
**	Writing functions
*/

void					write_from_start(t_st_cmd *st_cmd);
void					write_st_cmd(t_st_cmd *st_cmd);

/*
**	Arrow movement
*/

void					move_arrow_left(t_st_cmd *st_cmd);
void					move_arrow_right(t_st_cmd *st_cmd);
void					go_up(t_st_cmd *st_cmd);
void					go_down(t_st_cmd *st_cmd);
void					go_to_start(t_st_cmd *st_cmd);
void					go_to_end(t_st_cmd *st_cmd);

/*
**	Backspace and delete functions
*/

void					delete_right(t_st_cmd *st_cmd);
void					delete_left(t_st_cmd *st_cmd);
void					shift_chars_left(char *str, size_t shift_no);

/*
**	Copy/paste
*/

int						selector(t_st_cmd *st_cmd, char *buf, t_vars *vars);

/*
**	Jump words
*/

int						jump_words(t_st_cmd *st_cmd, int num);

/*
**	Input string manipulation
*/

size_t					ft_printable_len(const char *str);
char					*ft_strdup_print(const char *str);
void					insert_str(t_st_cmd *st_cmd, const char *buf,
		size_t printable_len);

#endif
