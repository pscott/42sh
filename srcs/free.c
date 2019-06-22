#include "ftsh.h"
#include "line_editing.h"
#include "lexer.h"
#include "ast.h"
#include "heredoc.h"

void		free_token_list(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		probe = probe->next;
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

void		free_ast(t_ast *ast_root)
{
	if (!ast_root)
		return ;
	if (ast_root->left)
		free_ast(ast_root->left);
	if (ast_root->right)
		free_ast(ast_root->right);
	free_ast_node(ast_root);
}

char		*free_get_doc(char *txt, char *eof)
{
	ft_strdel(&txt);
	ft_strdel(&eof);
	return (NULL);
}

void		ft_memdel_ntab(char ***ntab)
{
	ft_free_ntab(*ntab);
	*ntab = NULL;
}
