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

t_token	*copy_job_tokens(t_token *start)
{
	t_token *end;

	end = start;
	while (end && end->type <= tk_amp)
		end = end->next;
	return (copy_tokens_from_to(start, end));
}

t_token	*copy_process_tokens(t_token *start)
{
	t_token *end;

	end = start;
	while (is_simple_cmd_token(end))
		end = end->next;
	return (copy_tokens_from_to(start, end));
}
