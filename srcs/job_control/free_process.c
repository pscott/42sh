#include "jobs.h"

static void	free_process(t_process *p)
{
	free_token_list(p->token_list);
	ft_strdel(&p->process_str);
	ft_bzero(p, sizeof(*p));
	free(p);
}

void		free_process_list(t_process *p)
{
	t_process *next;

	while (p)
	{
		next = p->next;
		free_process(p);
		p = next;
	}
}
