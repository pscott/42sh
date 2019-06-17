#include "jobs.h"

static void	free_process(t_process *p)
{
	free_token_list(p->token_list);
	ft_bzero(p, sizeof(*p));
	free(p);
}

static void	free_process_list(t_process *p)
{
	t_process *next;

	while (p)
	{
		next = p->next;
		free_process(p);
		p = next;
	}
}

void		free_job(t_job *j)
{
	if (!j)
		return ;
	free_token_list(j->token_list);
	free_process_list(j->first_process);
	ft_bzero(j, sizeof(*j));
	free(j);
}

void		free_job_list(t_job *j)
{
	t_job *next;

	while (j)
	{
		next = j->next;
		free_job(j);
		j = next;
	}
}
