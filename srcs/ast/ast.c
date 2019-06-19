#include "ftsh.h"
#include "lexer.h"
#include "cmd_parsing.h"
#include "ast.h"

/*
** insert_ast_node
** recursively look for the correct spot to add node in ast
** 1. check if current spot is empty, insert here
** 2. check if new->type is >= current->type, if so:
** 	reroot current to new
** 3. if left is empty, insert left
** 4. insert right
*/

static int		insert_ast_node(t_ast *new, t_ast **root)
{
	t_token_type new_type;
	t_token_type root_type;

	if (!new)
		return (0);
	if (!*(root))
	{
		*root = new;
		return (1);
	}
	new_type = new->token->type == tk_or ? tk_and : new->token->type;
	root_type = (*root)->token->type == tk_or ? tk_and : (*root)->token->type;
	if (new_type >= root_type)
	{
		new->left = *root;
		*root = new;
		return (1);
	}
	else
	{
		if (!(*root)->left)
			return (insert_ast_node(new, &(*root)->left));
		else
			return (insert_ast_node(new, &((*root)->right)));
	}
}

/*
** add_last_node_to_ast
** insert the last token list to ast, unless it is full of TK_EAT
** set token_head to NULL, so create_ast() can return the ast to handle_input()
*/

static int		add_last_node_to_ast(t_token **token_head, t_ast **ast_root)
{
	if (!is_tklst_full_eat(*token_head))
	{
		if (!(insert_ast_node(create_ast_node(*token_head, NULL, NULL),
					ast_root)))
			return (0);
	}
	else
		free_token_list(*token_head);
	*token_head = NULL;
	return (1);
}

/*
** add_node_to_ast
** call find_next_ctrl_op() to place needed pointers
** then create and add ast_node to ast accordingly
*/

static int		add_node_to_ast(t_token **token_head, t_ast **ast_root)
{
	t_token	*token_probe;
	t_token	*token_prev;

	token_probe = *token_head;
	token_prev = NULL;
	if (!find_next_ctrl_op(&token_probe, &token_prev))
		return (add_last_node_to_ast(token_head, ast_root));
	else
	{
		if (token_prev)
			token_prev->next = NULL;
		if (!(insert_ast_node(create_ast_node(*token_head, NULL, NULL),
					ast_root)))
			return (0);
		*token_head = token_probe->next;
		token_probe->next = NULL;
		if (!(insert_ast_node(create_ast_node(token_probe, NULL, NULL),
					ast_root)))
			return (0);
	}
	return (1);
}

/*
** create_ast
** parse token_list and create ast from it
** each add_node_to_ast:
** - add 2 node to ast, 1 simple_cmd and 1 ctrl_op (except the last call)
** - move the token_head accordingly
*/

t_ast			*create_ast(t_token *token_head)
{
	t_ast	*ast_root;

	ast_root = NULL;
	while (token_head)
	{
		if (!(add_node_to_ast(&token_head, &ast_root)))
			return (NULL);
	}
	return (ast_root);
}

int				exec_ast(t_ast *root, t_vars *vars)
{
	int	ret;

	if (!root)
		return (1);
	if (root->token->type == tk_semi)
	{
		if ((ret = exec_ast(root->left, vars)) == 254 || ret == -2)
			return (1);
		vars->cmd_value = ret;
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
		return (parse_cmdline(root->token, vars));
}
