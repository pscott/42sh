#include "tosh.h"
#include "lexer.h"
#include "ast.h"

void	free_token_list(t_token *token_head)
{
	t_token	*probe;

///	ft_printf("freeing token list !!!!!!!");
// 	print_line();
	probe = token_head;
	while (probe)
	{
		probe = probe->next;
//		print_token(token_head);
		//free(token_head->content);
		ft_memdel((void*)&token_head->content);
		ft_memdel((void*)&token_head);
		token_head = probe;
	}
}

static void	free_ast_node(t_ast *node)
{
	free_token_list(node->token);
	ft_memdel((void*)&node);
}

void	free_ast(t_ast *ast_root)
{
	if (ast_root->left)
		free_ast(ast_root->left);
	if (ast_root->right)
		free_ast(ast_root->right);
	free_ast_node(ast_root);
}
