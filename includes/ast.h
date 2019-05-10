#ifndef AST_H
# define AST_H

#include "tosh.h"
#include "lexer.h"
#include <fcntl.h>

char **g_env;

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*
** t_simplecmd
** is a list of tokens making a single cmd
** with a redirection table
*/

typedef struct		s_simplecmd
{
	int				redir_table[4];
	char			**cmd_table;
}					t_simplecmd;

/*
** t_pipelst
** is a list of simplecmd
** redirection will be set as we parse the pipelst ??
*/

typedef struct		s_pipelst
{
	t_simplecmd			*simplecmd;
	struct s_pipelst	*next;
}					t_pipelst;

/*
** token_parser.c
*/

t_ast			*create_ast(t_token *token_head);
t_ast			*create_ast_node(t_token *new_token, t_ast *left
				, t_ast *right);
t_bool			is_tklst_full_eat(t_token *token_head);

/*
** Pipeline parsing
*/

int				parse_pipeline(t_token *token, char **env);
void			redirect(int old_fd, int new_fd);

t_bool			is_simple_cmd_token(t_token *probe);
t_token			**get_argv_from_tokens(t_token *token);

t_bool			is_argv_token(t_token *probe);

/*
** free
*/

void				free_ast(t_ast *ast_root);
void				free_token_list(t_token *token_head);

/*
** Redirections parsing
*/

t_bool			parse_redirections(t_token *token_head);
t_bool			is_quote_token(t_token *probe);
t_bool			parse_tildes(t_token *token_head, const char **env);
t_bool			replace_tilde(char **str, const char **env);
t_bool			parse_expands(t_token *token_head, int in, int out, char **env);
t_bool			parse_dollars(t_token *token_head, char **env);
t_bool			parse_quotes(t_token *token_head);
t_bool			execute_tokens(t_token *token_head);

t_bool			redir_great(t_token *redir, t_token *prev);
t_bool			redir_fd_great(t_token *redir, t_token *prev);
t_bool			redir_dgreat(t_token *redir, t_token *prev);
t_bool			redir_less(t_token *redir, t_token *prev);
t_bool			redir_dless(t_token *redir, t_token *prev);

int				check_fd_prev(t_token *prev);
t_bool			is_ctrl_op_token(t_token *token);

void			print_ast(t_ast *root);//debug

t_bool			exec_ast(t_ast *ast_root, char **env);
#endif
