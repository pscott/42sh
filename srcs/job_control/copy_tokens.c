#include "lexer.h"
#include "jobs.h"

t_token	*copy_tokens_from_to(t_token *from, t_token *to)
{
	t_token	*res;
	t_token	*probe;

	res = NULL;
	probe = from;
	while (probe && probe != to)
	{
		append_token(&res, create_token(probe->content, probe->size, probe->type));
		probe = probe->next;
	}
	return (res);
}

char	*copy_ast_tokens(t_ast *root)
{
	char *res;

	if (!root)
		return (NULL);
	if (!root->left)
		return (tokens_to_str(root->token));
	res = ft_strjoin_free_left(copy_ast_tokens(root->left), root->token->content);
	res = ft_strjoin_free_left(res, copy_ast_tokens(root->right));
	return (res);
}

char	*copy_job_tokens(t_ast *root)
{
	char	*res;
	t_ast	*new_root;

	if (!root)
		return (NULL);
	else if (!root->left)
		return (copy_ast_tokens(root));
	if (root->left->token->type == tk_amp)
		new_root = root->right;
	else
		new_root = root->left;
	res = copy_ast_tokens(new_root);
	return (res);
}

t_token	*copy_process_tokens(t_token *start)
{
	t_token *end;

	if (!(end = start))
		return (NULL);
	while (is_simple_cmd_token(end))
		end = end->next;
	return (copy_tokens_from_to(start, end));
}
