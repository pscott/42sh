#include "42sh.h"
#include "lexer.h"

void	print_token(t_token *token)//debug
{
	if (!token)
		return ;
	ft_printf("_TOKEN_ type:%d {%s}\n", token->type, token->content);
}

void	print_token_list(t_token *token_head)//debug
{
	t_token	*probe;

	ft_printf("--Printing token list--\n");
	probe = token_head;
	while (probe)
	{
		//printf("probe->next add: %p\n", probe);
		print_token(probe);
		probe = probe->next;
	}
}
