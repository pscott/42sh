#ifndef CMD_PARSING_H
# define CMD_PARSING_H

# include "ftsh.h"
# include "lexer.h"
# define IFS " \t\n"

int				parse_cmdline(t_token *token, t_vars *vars);
void			redirect(int old_fd, int new_fd, int save);

/*
** Expands parsing
*/

t_bool		parse_tildes(t_token *token_head, const char **env);
//t_bool		parse_param_sub(char **str, t_vars *vars);
t_bool		parse_vars(char **str, t_vars *vars);
t_bool		parse_arith_exp(char **str, t_vars *vars);
//t_bool		parse_env_var(char **str, t_vars *vars);
t_bool		parse_quotes(t_token *token_head);
t_bool		parse_expands(t_token *token_head, t_vars *vars);
t_bool		parse_dollars_str(char **str, t_vars *vars);

/*
** substitute_utils
*/

t_bool		is_terminated(const char *open_pattern, const char *close_pattern
			, const char *str);
t_bool		is_matched(const char *str
			, const char *begin_match, const char *end_match);
t_bool		substitute_slice(char **old_str, size_t index[2]
			, const char *to_sub);




char		*get_var_name(char *str);//change place ?
t_bool		replace_tilde(char **str, const char **env);
t_bool		is_valid_tilde(const char *str, t_token *prev_token);



/*
**	Redirections parsing
*/

t_bool			parse_redirections(t_token *token_head, int mode);
t_bool			redir_great(t_token *redir, t_token *prev, int mode);
t_bool			redir_fd_great(t_token *redir, t_token *prev, int mode);
t_bool			redir_fd_less(t_token *redir, t_token *prev, int mode);
t_bool			redir_dgreat(t_token *redir, t_token *prev, int mode);
t_bool			redir_less(t_token *redir, t_token *prev, int mode);
int				check_fd_prev(t_token *prev);

#endif
