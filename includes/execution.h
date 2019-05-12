#ifndef EXECUTION_H
#define EXECUTION_H

char		*get_cmd_path(char **argv, char **env);
char		**get_argv_from_token_lst(t_token *token);
t_bool		execute_in_fork(t_token *token_head, int in, int out, t_vars *vars);
t_bool		execute_builtin_no_fork(t_token *token_head, t_vars *vars);

#endif
