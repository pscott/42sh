#ifndef CMD_PARSING_H
# define CMD_PARSING_H

# include "lexer.h"
# include <pwd.h>
# include "ast.h"

# define IFS " \t\n"
# define BANG_MAX 80

int					parse_cmdline(t_ast *root, t_vars *vars, int foreground);
void				redirect(int old_fd, int new_fd, int save);

/*
** Expands parsing
*/

int					parse_tildes(t_token *token_head, const char **env);
int					parse_vars(char **str, t_vars *vars);
int					parse_arith_exp(char **str, t_vars *vars);
int					parse_quotes(t_token *token_head);
int					parse_bangs(t_token *token_head, int mode);
int					parse_expands(t_token *token_head, t_vars *vars);
int					parse_dollars_str(char **str, t_vars *vars);
int					parse_assignation(t_token *token, t_vars *vars);
void				apply_assignation(char ***assign_tab, t_vars *vars);
void				apply_assignation_to_ntab(char ***assign_tab, char ***ntab);

/*
** Parse bangs utils
*/

void				refresh_i(int nb, int *i, int ret);
int					is_quoted_char(char *s, int i, char c);
int					go_to_matching_sqt(char **str, int *i);

/*
** substitute_utils
*/

int					is_terminated(const char *open_pattern,
					const char *close_pattern, const char *str);
int					is_matched(const char *str, const char *begin_match,
					const char *end_match);
int					substitute_slice(char **old_str, size_t index[2],
					const char *to_sub);
int					is_valid_varname(char *str);
char				*get_var_name(char *str);
int					replace_tilde(char **str, const char **env);
int					replace_bang(char **str, int mode);
int					is_valid_tilde(const char *str, t_token *prev_token);
int					is_slashed(const char *str);
int					set_escaped(int escpaed, char c);
void				substitute_cmd_value(char **str, size_t *i, t_vars *vars);
char				*lltoa_and_free(long long nb, char **to_free);

/*
**	Redirections parsing
*/

int					parse_redirections(t_token *token_head, int mode);
int					redir_great(t_token *redir, t_token *prev, int mode);
int					redir_fd_great(t_token *redir, t_token *prev, int mode);
int					redir_fd_less(t_token *redir, t_token *prev, int mode);
int					redir_dgreat(t_token *redir, t_token *prev, int mode);
int					redir_less(t_token *redir, t_token *prev, int mode);
int					check_fd_prev(t_token *prev);
int					check_redirect(char *str);
void				save_close_fds(int new_fd, int old_fd);

/*
** Errors
*/

int					bad_fd_error(int fd, int mode);
int					ambi_redir_error(char *str, int mode);
int					get_new_fd(t_token *next, int mode, int *new_fd);
int					errors_fd_great(char *token, int err, int fd, int mode);
int					check_redirects(char *str);
int					change_token_close(t_token *next);
int					no_file_error(char *filename, int mode);
int					open_error(char *filename, int mode);

/*
**	Saves of opens and fds which are not stdfds
*/

typedef struct		s_c_lst
{
	int				fd;
	struct s_c_lst	*next;
}					t_c_lst;

void				save_close_openfds(int fd, int mode);

#endif
