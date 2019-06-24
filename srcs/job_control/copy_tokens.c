#include "lexer.h"
#include "jobs.h"
#include "cmd_parsing.h"

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
	char	*res;
	char	*left;
	char	*right;

	if (!root)
		return (NULL);
	if (!root->left)
		return (tokens_to_str(root->token, tk_amp));
	left = ft_strjoin_free_left(copy_ast_tokens(root->left), root->token->content);
	right = copy_ast_tokens(root->right);
	res = ft_strjoin_free_left(left, right);
	ft_strdel(&right);
	return (res);
}

static char	*ntab_to_str(char **split)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (split[i])
	{
		res = ft_strjoin_free_left(res, split[i]);
		res = ft_strjoin_free_left(res, " ");
		i++;
	}
	return (res);
}

char	*copy_job_tokens(t_ast *root)
{
	char	*res;
	char	**split;

	if (!root)
		return (NULL);
	res = copy_ast_tokens(root);
	if (!(split = ft_strsplit(res, " ")))
		clean_exit(1, 1);
	ft_strdel(&res);
	res = ntab_to_str(split);
	ft_free_ntab(split);
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
