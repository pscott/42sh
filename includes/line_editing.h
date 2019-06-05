#ifndef LINE_EDITING_H
# define LINE_EDITING_H

#include "input.h"

/*
**	Window struct
*/

void						update_window_struct(struct winsize *window);
struct winsize				*init_window_struct(void);

/*
**	On-screen position functions
*/

void						init_relative_pos(t_st_cmd *st_cmd);
void						update_start_pos(t_st_cmd *st_cmd);
void						get_pos(t_st_cmd *st_cmd, size_t tracker);
void						go_back_to_start(t_st_cmd *st_cmd);
void						reposition_cursor(t_st_cmd *st_cmd);

/*
**	Writing functions
*/
int							write_line(t_st_cmd *st_cmd);
void						write_st_cmd(t_st_cmd *st_cmd);
void						write_from_start(t_st_cmd *st_cmd);

#endif
