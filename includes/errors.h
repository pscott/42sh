#ifndef ERRORS_H
# define ERRORS_H
# define SN SHELL_NAME

# include "lexer.h"

# define ERR_CMD 127
# define ERR_CMD_STR SN ": command not found"

# define ERR_GNL 3
# define ERR_GNL_STR SN ": get_next_line() failed"

# define ERR_NOEXIST 1
# define ERR_NOEXIST_STR SN ": no such file or directory"

# define ERR_FORK 5
# define ERR_FORK_STR SN ": fork() failed"

# define ERR_PERM 6
# define ERR_PERM_STR SN ": permission denied"

# define ERR_OPEN 7
# define ERR_OPEN_STR SN ": could not open"

# define ERR_CLOSE 8
# define ERR_CLOSE_STR SN ": close() failed"

# define ERR_NOT_SET 9
# define ERR_NOT_SET_STR SN ": variable not set"

# define ERR_TERMENTR 10
# define ERR_TERMENTR_STR SN ": no data for terminal name"

# define ERR_TERMDATA 11
# define ERR_TERMDATA_STR SN ": terminfo database could not be found"

# define ERR_TCGET 12
# define ERR_TCGET_STR SN ": tcgetattr() failed"

# define ERR_TCSET 13
# define ERR_TCSET_STR SN ": tcsetattr() failed."

# define ERR_OPENDIR 14
# define ERR_OPENDIR_STR SN ": opendir() failed"

# define ERR_CLOSEDIR 15
# define ERR_CLOSEDIR_STR SN ": closedir() failed"

# define ERR_GETCWD 16
# define ERR_GETCWD_STR SN ": getcwd() failed"

# define ERR_LSTAT 17
# define ERR_LSTAT_STR SN ": lstat() failed"

# define ERR_READ 18
# define ERR_READ_STR SN ": read() failed"

# define ERR_MALLOC 20
# define ERR_MALLOC_STR SN ": malloc() failed"

# define ERR_CHDIR 21
# define ERR_CHDIR_STR SN ": chdir() failed"

# define ERR_GETENV 22
# define ERR_GETENV_STR SN ": get_env()failed"

# define ERR_NOTDIR 23
# define ERR_NOTDIR_STR SN ": not a directory"

# define ERR_TERM_DEVICE 23
# define ERR_TERM_DEVICE_STR SN ": unable to open the terminal device file"

# define ERR_IOCTL 23
# define ERR_IOCTL_STR SN ": unable to get terminal state infos with ioctl()"

# define ERR_TERMNAME 23
# define ERR_TERMNAME_STR SN ": terminal name could not be found (get_env())"

# define ERR_NO_OLDPWD 24
# define ERR_NO_OLDPWD_STR SN ": old pwd not set"

# define ERR_EXECUTE 25
# define ERR_EXECUTE_STR SN ": failed to execute"

# define ERR_MAX_INPUT 26
# define ERR_MAX_INPUT_STR SN ": maximum input size exceeded"

# define ERR_EVENT_NOT_FOUND 27
# define ERR_EVENT_NOT_FOUND_STR SN ": event not found"

# define ERR_OPEN_FC_STR SN "fc: an open() error occured"

void	error_exit(int errno, const char *str_err, const char *err_file);
int		print_errors(int errno, const char *err_str, const char *err_file);
void	syntax_error_near(t_token *token);
#endif
