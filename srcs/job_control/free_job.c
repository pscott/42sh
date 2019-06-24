#include "jobs.h"

/*
**	Frees specified job from list.
**	Returns the last job before the free'd job.
*/

t_job		*free_job_from_list(t_job *delete)
{
	t_job	*j;
	t_job	*jlast;

	if (!delete || !(j = g_first_job))
		return (free_job(&delete));
	else if (delete == j)
	{
		g_first_job = j->next ? j->next : NULL;
		free_job(&delete);
		return (g_first_job);
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

void		*free_job(t_job **j)
{
	if (!j || !*j)
		return (NULL);
	ft_strdel(&(*j)->command);
	free_process_list((*j)->first_process);
	ft_bzero((*j), sizeof(**j));
	free(*j);
	*j = NULL;
	return (NULL);
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
