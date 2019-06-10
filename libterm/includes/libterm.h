/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libterm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/06/10 12:37:19 by pscott           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTERM_H
# define LIBTERM_H

# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include "libft.h"
# include "cursor.h"

/*
** FILE DESCRIPTORS
*/

# define TERM_FD 54
# define ESC "\x1b"

/*
** ARROWS ANSCII ESCAPE CODES
*/

# define LEFTARROW "\x1b\x5b\x44"
# define RIGHTARROW "\x1b\x5b\x43"
# define DOWNARROW "\x1b\x5b\x42"
# define UPARROW "\x1b\x5b\x41"
# define ARROW_LEN 3

/*
** SPACE, TAB, REVERSE TAB, ESCAPE, BACKSPACE, DELETE, ENTER
*/

# define SPACE "\x20"
# define SPACE_LEN 1
# define ENTER "\r"
# define ENTER_LEN 1
# define ESCAPE "\x1b"
# define ESCAPE_LEN 1
# define BACKSPACE "\x7f"
# define BACKSPACE_LEN 1
# define DEL "\x1b\x5b\x33\x7e"
# define DEL_LEN 4
# define HOME "\x1b\x5b\x48"
# define HOME_LEN 3

# define END "\x1b\x5b\x46"
# define END_LEN 3

# define BELL "\x07"
# define BELL_LEN 1
# define CTRL_Z "\x1a"
# define CTRL_Z_LEN 1
# define CTRL_D "\x04"
# define CTRL_Z_LEN 1
# define CTRL_C "\x03"
# define CTRL_C_LEN 1
# define CTRL_R "\x12"
# define CTRL_R_LEN 1

# define ALT_X "\xe2\x89\x88"
# define ALT_X_LEN 3
# define ALT_C "\xc3\xa7"
# define ALT_C_LEN 2
# define ALT_V "\xe2\x88\x9a"
# define ALT_V_LEN 3

# define ALT_UP "\x1b\x1b\x5b\x41"
# define ALT_UP_LEN 4
# define ALT_DOWN "\x1b\x1b\x5b\x42"
# define ALT_DOWN_LEN 4
# define ALT_RIGHT "\x1b\x1b\x5b\x43"
# define ALT_RIGHT_LEN 4
# define ALT_LEFT "\x1b\x1b\x5b\x44"
# define ALT_LEFT_LEN 4

/*
** Previous terminal settings are saved in a global, and restored on exit.
*/

static struct termios	g_saved_attr;
static int				g_isatty = 0;

/*
** Settings-related functions
*/

int						setup_terminal_settings(void);
int						reset_terminal_settings(void);
int						check_caps(void);

/*
** Executes the corresponding termcap string
*/

int						execute_str(char *cap);
int						put_special_fd(int c);

/*
** Error functions
*/

int						err_getattr(void);
int						err_not_terminal(void);
int						err_no_env(void);
int						err_setattr(void);
int						err_resetattr(void);
int						err_noentry(void);
int						err_no_database(void);
int						err_no_env(void);
int						err_tgoto(char *cap);
int						err_caps(void);

#endif
