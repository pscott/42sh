#ifndef EXECUTION_H
#define EXECUTION_H

#include "lexer.h"

char		*get_cmd_path(char **argv, char **env);
char		**get_argv_from_token_lst(t_token *token);
t_bool		execute_in_fork(t_token *token_head, int in, int out, t_vars *vars);
t_bool		execute_only_one_cmd(t_token *begin, t_vars *vars);
int			check_access(char *file);//TODO const plz
char		*find_path(char *file, char **paths);

#endif
