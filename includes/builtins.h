#ifndef BUILTINS_H
# define BUILTINS_H

# include "errors.h"

enum	{CMD_CD = 1, CMD_ECHO, CMD_ENV, CMD_EXIT, CMD_SETENV, CMD_UNSETENV};
int		check_builtins(char **argv);
int		exec_builtins(char **argv, int cmd_id);

int		case_cd(char **argv);

#endif
