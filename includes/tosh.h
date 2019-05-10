#ifndef TOSH_H
# define TOSH_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "lexer.h"
# include "ast.h"
# include "reader.h"
# define SHELL_NAME "my_sh"
# define FD_LIMITS 10
# define ERROR_READ exit(1);//TODO

typedef unsigned char	t_bool;

/*
** main.c
*/

/*
** init_env.c
*/

char				**init_env(const char **env);

/*
** shlvl.c
*/

void				set_shlvl(char ***env);

/*
** environ_utils.c
*/

int					get_envline_index(char *search, char **env);
char				*get_envline_value(char *search, char **env);
char				*get_envline(char *search, char **env);

/*
** environ_set.c
*/

void				set_env_var(char *var_name, char *var_value, char ***env);


/*
** handle_input.c
*/

t_bool				handle_input(t_st_cmd *st_cmd, char **env);

/*
** lexer.c
*/

t_token				*create_token(char *cmdline, size_t size
					, t_token_type type);
//t_bool				add_token_to_list(t_token *current_token
//					, t_token *prev_token, t_token **token_head);
//t_token				*lexer(char *cmdline, char **env);
int					lexer(char *cmdline, t_token **token_head, char **env);

/*
** lexer_tools.c
*/

t_bool				is_quotes(char c);
t_bool				is_white_spaces(char c);
t_bool				is_delimiter(char c);
t_bool				is_metachar(char c);
t_bool				is_logic_or_pipe(t_token *token);
t_bool				is_two_ctrlop_or_redir_following(t_token *prev_token
					, t_token *current_token);
t_bool				token_list_start_with_ctrl_op(t_token *prev_token
					, t_token *current_token);
t_bool				is_redir_token(t_token *token);

t_bool				is_full_of_whitespaces(char *input);

#endif
