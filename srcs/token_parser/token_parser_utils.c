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
		if (probe->type > tk_eat)
			return (0);
		probe = probe->next;
	}
	return (1);
}

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= tk_and)
		return (1);
	return (0);
}

//TODO move exec_ast to another file ?
int		exec_ast(t_ast *root, t_vars *vars)
{
	int	ret;

	if (!root)
		return (0);
	if (root->token->type == tk_semi)//TK_AMP
	{
		if ((ret = exec_ast(root->left, vars)) > 0)
			return (ret);
		return (exec_ast(root->right, vars));
	}
	else if (root->token->type == tk_and)
		return (exec_ast(root->left, vars) || exec_ast(root->right, vars));
	else if (root->token->type == tk_or)
		return (exec_ast(root->left, vars) && exec_ast(root->right, vars));
	else
	{
		ft_printf("==Begin Exec==\n");
		return (parse_cmdline(root->token, vars));
	}
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
