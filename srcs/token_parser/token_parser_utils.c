#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
** create_ast_node
** malloc a new ast_node and return a pointer to it
*/

t_ast	*create_ast_node(t_token *new_token, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(*new_node))))
		ERROR_MEM;
	new_node->token = new_token;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

/*
** is_tklst_full_eat
** just check if the given token list is full of eat tokens
*/

t_bool	is_tklst_full_eat(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		if (probe->type > TK_EAT)
			return (0);
		probe = probe->next;
	}
	return (1);
}

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= TK_AND)
		return (1);
	return (0);
}

//TODO move exec_ast to another file ?
t_bool	exec_ast(t_ast *root, char **env)
{
	if (!root)
		dprintf(2, "Error: NULL node\n");
	if (root->token->type == TK_SEMI)//TK_AMP
	{
		exec_ast(root->left, env);
		if (root->right)//penzo added this
			return (exec_ast(root->right, env)); // check if that's true
		else
			return (1);//penzo test
	}
	else if (root->token->type == TK_AND)
		return (exec_ast(root->left, env) || exec_ast(root->right, env));
	else if (root->token->type == TK_OR)
		return (exec_ast(root->left, env) && exec_ast(root->right, env));
	else
		return (parse_pipeline(root->token, env));
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
