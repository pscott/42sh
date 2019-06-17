#include "jobs.h"

t_process *create_process(t_token *token_list, pid_t pid)
{
	t_process *p;

	if (!(p = malloc(sizeof(t_process))))
		clean_exit(1, 1);
	p->next = NULL;
	p->token_list = token_list;
	p->pid = pid;
	p->completed = 0;
	p->stopped = 0;
	p->status = 0;
	return (p);
}

/*
**	Appends the to_add process to the list of processes.
**	Returns the last process appended for faster insertion.
*/

t_process		*append_process(t_process **first_process, t_process *to_add)
{
	t_process	probe;

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
