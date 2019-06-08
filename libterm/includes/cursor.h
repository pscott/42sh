/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/08 19:50:07 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

# include "libft.h"
# include <unistd.h>

# define POS_BUF_SIZE 63
# define GET_POS "\x1b\x5b\x36\x6e"
# define BEGIN_LINE "cr"
# define LEFT_CORNER "ho"
# define MOVE_CURSOR "cm"
# define SAVE_CURSOR "sc"
# define RESTORE_CURSOR "rc"
# define INVISIBLE "vi"
# define VISIBLE "ve"
# define CLEAR "cl"
# define CLEAR_BELOW "cd"
# define PRINT_LINE "do"
# define ERASE_ENDLINE "ce"
# define HIGHLIGHT "so"
# define NO_HIGHLIGHT "se"
# define UNDERLINE "us"
# define NO_UNDERLINE "ue"
# define SCROLL_DOWN "sf"
# define MOVE_UP "up"
# define NUM_CAPS 17

typedef struct	s_pos {
	int	row;
	int	col;
}				t_pos;
void			retrieve_pos(t_pos *curr_pos);
int				move_cursor(int col, int row);
int				is_valid_pos_format(char *pos_str);

#endif
