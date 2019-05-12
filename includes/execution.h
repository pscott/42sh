#ifndef EXECUTION_H
#define EXECUTION_H

char		*get_cmd_path(char **argv);
char		**get_argv_from_token_lst(t_token *token);
t_bool		execute_in_fork(t_token *token_head, int in, int out, char **env);
t_bool		execute_builtin_no_fork(t_token *token_head, char **env);

#endif
