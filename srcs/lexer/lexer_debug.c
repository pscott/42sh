#include "ftsh.h"
#include "lexer.h"

//TODO tej me before last push

void	print_token(t_token *token)
{
	if (!token)
		return ;
	ft_dprintf(2, "_TOKEN_ type:%d {%s}\n", token->type, token->content);
}

void	print_token_list(t_token *token_head)
{
	t_token	*probe;

	ft_dprintf(2, "--Printing token list--\n");
	probe = token_head;
	while (probe)
	{
		print_token(probe);
		probe = probe->next;
	}
}
