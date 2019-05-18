#ifndef CMD_PARSING_H
# define CMD_PARSING_H

# include "42sh.h"
# include "lexer.h"

int				parse_pipeline(t_token *token, t_vars *vars);
void			redirect(int old_fd, int new_fd);

/*
** Expands parsing
*/

t_bool			parse_tildes(t_token *token_head, const char **env);
t_bool			replace_tilde(char **str, const char **env);
t_bool			parse_expands(t_token *token_head, char **env);
t_bool			parse_dollars(t_token *token_head, char **env);
t_bool			parse_quotes(t_token *token_head);

/*
**	Redirections parsing
*/
t_bool			parse_redirections(t_token *token_head);
t_bool			redir_great(t_token *redir, t_token *prev);
t_bool			redir_fd_great(t_token *redir, t_token *prev);
t_bool			redir_dgreat(t_token *redir, t_token *prev);
t_bool			redir_less(t_token *redir, t_token *prev);
t_bool			redir_dless(t_token *redir, t_token *prev);
int				check_fd_prev(t_token *prev);


#endif
