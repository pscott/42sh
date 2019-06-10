#include "ftsh.h"
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

/*
** find_next_ctrl_op
** move the given pointer:
** - token_probe to the next ctrl_op or NULL if it's the end of token list
** - token_prev to the last non-eat token encounter
** return 0 if it reach the end of the token list
** return 1 otherwise (token_probe is on an CTRL_OP token)
*/

int		find_next_ctrl_op(t_token **token_probe, t_token **token_prev)
{
	while (*token_probe && !(is_ctrl_op_token(*token_probe)))
	{
		*token_prev = *token_probe;
		*token_probe = (*token_probe)->next;
	}
	if (*token_probe)
		return (1);
	return (0);
}
