#ifndef EXECUTION_H
#define EXECUTION_H

#include "lexer.h"

char		*get_cmd_path(char **argv, char **env, int verbose);
char		**get_argv_from_token_lst(t_token *token);
t_bool		parse_and_exec(t_token *token_head, int in, int out, t_vars *vars);
t_bool		execute_no_pipe_builtin(t_token *begin, t_vars *vars);
int			check_access(const char *file);//TODO const plz
char		*find_path(char *file, char **paths);

#endif
