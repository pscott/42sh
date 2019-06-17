#include "jobs.h"

static void	free_process(t_process *p)
{
	ft_bzero(process, sizeof(*p));
	free(p);
}

void		free_job(t_job *j)
{
	t_process	*p;
	t_process	*next;

	if (!j)
		return ;
	ft_strdel(&j->command);
	p = j->first_process;
	while (p)
	{
		next = p->next;
		free_process(p);
		p = next;
	}
	ft_bzero(j, sizeof(*j));
	free(j);
}
