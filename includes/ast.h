#ifndef AST_H
# define AST_H

# include "lexer.h"

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*
** token_parser.c
*/

t_ast			*create_ast(t_token *token_head);
t_ast			*create_ast_node(t_token *new_token, t_ast *left
				, t_ast *right);
t_bool			is_tklst_full_eat(t_token *token_head);

void				free_ast(t_ast *ast_root);

void			print_ast(t_ast *root);//debug
int				exec_ast(t_ast *ast_root, t_vars *vars);

#endif
