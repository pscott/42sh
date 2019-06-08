#include "ftsh.h"
#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

/*
** create_ast_node
** malloc a new ast_node and return a pointer to it
*/

t_ast	*create_ast_node(t_token *new_token, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(*new_node))))
		clean_exit(1, 1);
	new_node->token = new_token;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

/*
** is_tklst_full_eat
** just check if the given token list is full of eat tokens
*/

int		is_tklst_full_eat(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		if (probe->type > tk_eat)
			return (0);
		probe = probe->next;
	}
	return (1);
}

int		is_ctrl_op_token(t_token *token)
{
	if (token->type >= tk_and)
		return (1);
	return (0);
}

int		exec_ast(t_ast *root, t_vars *vars)
{
	int	ret;

	if (!root)
		return (1);
	if (root->token->type == tk_semi)
	{
		if ((ret = exec_ast(root->left, vars)) == 254 || ret == -2)
			return (1);
		return (exec_ast(root->right, vars));
	}
	else if (root->token->type == tk_and)
	{
		ret = exec_ast(root->left, vars);
		return (ret ? ret : exec_ast(root->right, vars));
	}
	else if (root->token->type == tk_or)
	{
		ret = exec_ast(root->left, vars);
		return (ret ? exec_ast(root->right, vars) : ret);
	}
	else
		return (ret = parse_cmdline(root->token, vars));
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
