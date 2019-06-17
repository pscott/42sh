#include "jobs.h"
#include "cmd_parsing.h"

t_process *create_process(t_token *token_list)
{
	t_process *p;

	if (!(p = malloc(sizeof(t_process))))
		clean_exit(1, 1);
	ft_bzero(p, sizeof(t_process));
	p->token_list = copy_process_tokens(token_list);
	return (p);
}

/*
**	Appends the to_add process to the list of processes.
**	Returns the last process appended for faster insertion.
*/

t_process		*append_process(t_process **first_process, t_process *to_add)
{
	t_process	*probe;

	if (!to_add)
		return (*first_process);
	if (!(probe = *first_process))
		*first_process = to_add;
	else
	{
		while (probe->next)
			probe = probe->next;
		probe->next = to_add;
	}
	return (to_add);
}

t_process *create_process_list(t_token *tokens)
{
	t_process *p;

	p = NULL;
	append_process(&p, create_process(tokens));
	while ((tokens = get_next_simple_command(tokens)))
		append_process(&p, create_process(tokens));
	return (p);
}

int		get_processes_len(t_process *p)
{
	int	i;

	i = 0;
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}
