#include "tosh.h"

void	print_token(t_token *token)//debug
{
	ft_printf("_TOKEN_ type:%d {%s}", token->type, token->content);
	print_line();
}

void	print_token_list(t_token *token_head)//debug
{
	t_token	*probe;

	ft_printf("--Printing token list--");
	print_line();
	probe = token_head;
	while (probe)
	{
		//printf("probe->next add: %p\n", probe);
		print_token(probe);
		probe = probe->next;
	}
}
