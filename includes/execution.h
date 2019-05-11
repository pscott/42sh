#ifndef EXECUTION_H
#define EXECUTION_H

# include "lexer.h" //for token

t_bool		execute_in_fork(t_token *token_head, int in, int out, char **env);
t_bool		execute_builtin_no_fork(t_token *token_head, char **env);
t_bool		execute_argv(char **argv);

#endif
