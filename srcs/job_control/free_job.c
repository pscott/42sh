#include "jobs.h"

static void	free_process(t_process *p)
{
	free_token_list(p->token_list);
	ft_bzero(p, sizeof(*p));
	free(p);
}

void	free_process_list(t_process *p)
{
	t_process *next;

	while (p)
	{
		next = p->next;
		free_process(p);
		p = next;
	}
}

/*
**	Frees specified job from list.
**	Returns the last job before the free'd job.
*/

t_job		*free_job_from_list(t_job *delete)
{
	t_job	*j;
	t_job	*jlast;

	if (!delete || !(j = g_first_job))
	{
		free_job(&delete);
		return (NULL);
	}
	if (delete == j)
	{
		if (j->next)
			g_first_job = j->next;
		else
			g_first_job = NULL;
		free_job(&delete);
		return (NULL);
	}
	jlast = j;
	while ((j = j->next))
	{
		if (j == delete)
		{
			jlast->next = j->next;
			free_job(&j);
			return (jlast);
		}
		jlast = j;
	}
	return (NULL);
}

void		free_job(t_job **j)
{
	if (!j || !*j)
		return ;
	ft_strdel(&(*j)->command);
	free_process_list((*j)->first_process);
	ft_bzero((*j), sizeof(**j));
	free(*j);
	*j = NULL;
}

void		free_job_list(t_job *j)
{
	t_job *next;

	while (j)
	{
		next = j->next;
		free_job(&j);
		j = next;
	}
}
