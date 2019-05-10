/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libterm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscott <pscott@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:40 by pscott            #+#    #+#             */
/*   Updated: 2019/05/08 18:04:29 by pscott           ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
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
# define TAB "\x09"
# define TAB_LEN 1
# define RTAB "\x1b\x5b\x5a"
# define RTAB_LEN 3
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

/*
** Previous terminal settings are saved in a global, and restored on exit.
*/

struct termios	g_saved_attr;
int				g_tty;

/*
** Settings-related functions
*/

int				setup_terminal_settings(void);
int				reset_terminal_settings(void);

/*
** Executes the corresponding termcap string
*/

int				execute_str(char *cap);

/*
** Function for printing line and outputing msgs with endline
*/

int				print_line(void);
void			term_putstr_endline(char *str, int fd);

/*
** Error functions
*/
int				err_getattr(void);
int				err_not_terminal(void);
int				err_no_env(void);
int				err_setattr(void);
int				err_resetattr(void);
int				err_noentry(void);
int				err_no_database(void);
int				err_no_env(void);
int				err_tgoto(char *cap);
int				err_no_str(char *cap);
int				err_caps(void);

#endif
