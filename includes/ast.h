#ifndef AST_H
# define AST_H

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*
** token_parser.c
*/

t_ast				*create_ast(t_token *token_head);
t_ast				*create_ast_node(t_token *new, t_ast *left, t_ast *right);
int					is_tklst_full_eat(t_token *token_head);

void				free_ast(t_ast *ast_root);

int					exec_ast(t_ast *ast_root, t_vars *vars);

/*
**	Debug
*/

void				print_ast(t_ast *root);

#endif
