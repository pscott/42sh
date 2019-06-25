#ifndef EXECUTION_H
# define EXECUTION_H

# include "lexer.h"

//char		*get_cmd_path(char *str, char **env, int verbose);
char		*get_cmd_path(char *str, t_vars *vars, int verbose);
int			get_argv_from_token_lst(t_token *token, char ***argv);
int			parse_and_exec(t_token *token_head, int in, int out, t_vars *vars);
int			check_no_pipe_builtin(t_token *begin, t_vars *vars);
int			check_access(const char *file);
char		*find_path(const char *file, char **paths);
int			exit_status(int status);
int			exec_bin(char **argv);

#endif
