#ifndef ERRORS_H
# define ERRORS_H

#include "lexer.h"

# define ERR_CMD 2
# define ERR_CMD_STR "error: command not found"

# define ERR_GNL 3
# define ERR_GNL_STR "error: get_next_line() failed"

# define ERR_NOEXIST 4
# define ERR_NOEXIST_STR "error: no such file or directory"

# define ERR_FORK 5
# define ERR_FORK_STR "error: fork() failed"

# define ERR_ACCESS 6
# define ERR_ACCESS_STR "error: permission denied"

# define ERR_OPEN 7
# define ERR_OPEN_STR "error: could not open"

# define ERR_CLOSE 8
# define ERR_CLOSE_STR "error: close() failed"

# define ERR_TERMENTR 10
# define ERR_TERMENTR_STR "error: no data for terminal name"

# define ERR_TERMDATA 11
# define ERR_TERMDATA_STR "error: terminfo database could not be found"

# define ERR_TCGET 12
# define ERR_TCGET_STR "error: tcgetattr() failed"

# define ERR_TCSET 13
# define ERR_TCSET_STR "error: tcsetattr() failed. Impossible to apply capacities."

# define ERR_OPENDIR 14
# define ERR_OPENDIR_STR "error: opendir() failed"

# define ERR_CLOSEDIR 15
# define ERR_CLOSEDIR_STR "error: closedir() failed"

# define ERR_GETCWD 16
# define ERR_GETCWD_STR "error: getcwd() failed"

# define ERR_LSTAT 17
# define ERR_LSTAT_STR "error: lstat() failed"

# define ERR_READ 18
# define ERR_READ_STR "error: read() failed"

# define ERR_MALLOC 20
# define ERR_MALLOC_STR "error: malloc() failed"

# define ERR_CHDIR 21
# define ERR_CHDIR_STR "error: chdir() failed"

# define ERR_GETENV 22
# define ERR_GETENV_STR "error: get_env()failed"

# define ERR_NOTDIR 23
# define ERR_NOTDIR_STR "error: this is not a directory"

# define ERR_TERM_DEVICE 23
# define ERR_TERM_DEVICE_STR "error: unable to open the terminal device file"

# define ERR_IOCTL 23
# define ERR_IOCTL_STR "error: unable to get terminal state infos with ioctl()"
# define ERR_TERMNAME 23
# define ERR_TERMNAME_STR "error: terminal name could not be found with get_env()"

# define ERR_NO_OLDPWD 24
# define ERR_NO_OLDPWD_STR "error: old pwd not set"

void	error_exit(int errno, char *str_err, char *err_file);
int		print_errors(int errno, char *err_str, char *err_file);
void	syntax_error_near(t_token *token);
#endif
