#ifndef CMD_PARSING_H
# define CMD_PARSING_H

# include "lexer.h"
# define IFS " \t\n"

int				parse_cmdline(t_token *token, t_vars *vars);
void			redirect(int old_fd, int new_fd, int save);

/*
** Expands parsing
*/

int				parse_tildes(t_token *token_head, const char **env);
int				parse_vars(char **str, t_vars *vars);
int				parse_arith_exp(char **str, t_vars *vars);
int				parse_quotes(t_token *token_head);
int				parse_expands(t_token *token_head, t_vars *vars);
int				parse_dollars_str(char **str, t_vars *vars);

/*
** substitute_utils
*/

int				is_terminated(const char *open_pattern,
					const char *close_pattern, const char *str);
int				is_matched(const char *str, const char *begin_match,
					const char *end_match);
int				substitute_slice(char **old_str, size_t index[2],
				const char *to_sub);

char			*get_var_name(char *str);
int				replace_tilde(char **str, const char **env);
int				is_valid_tilde(const char *str, t_token *prev_token);
int				is_slashed(const char *str);

/*
**	Redirections parsing
*/

int				parse_redirections(t_token *token_head, int mode);
int				redir_great(t_token *redir, t_token *prev, int mode);
int				redir_fd_great(t_token *redir, t_token *prev, int mode);
int				redir_fd_less(t_token *redir, t_token *prev, int mode);
int				redir_dgreat(t_token *redir, t_token *prev, int mode);
int				redir_less(t_token *redir, t_token *prev, int mode);
int				check_fd_prev(t_token *prev);

#endif
