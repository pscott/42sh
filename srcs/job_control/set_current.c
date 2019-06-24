#include "jobs.h"

static void set_plus(t_job *j)
{
	t_job	*res;
	t_job	*probe;

	res = NULL;
	probe = j;
	while (probe)
	{
		if (job_is_stopped(probe))
			res = probe;
		 probe = probe->next;
	}
	if (!res)
	{
		probe = j;
		while (probe)
		{
			if (!j->fg)
				res = probe;
			probe = probe->next;
		}
	}
	if (res)
		res->current = '+';
}

static void set_minus(t_job *j)
{
	t_job	*res;
	t_job	*last;
	t_job	*probe;

	last = NULL;
	res = NULL;
	probe = j;
	while (probe)
	{
		if (job_is_stopped(probe))
		{
			last = res;
			res = probe;
		}
		 probe = probe->next;
	}
	if (!last)
	{
		probe = j;
		while (probe->next)
		{
			if (!j->fg)
			{
				last = res;
				res = probe;
			}
			probe = probe->next;
		}
		if (probe)
			if (probe->current != '+')
				last = probe;
	}
	if (last)
		last->current = '-';
}

static void	clean_current(t_job *j)
{
	while (j)
	{
		j->current = ' ';
		j = j->next;
	}
}


void	set_current(void)
{
	t_job	*j;

	if (!(j = g_first_job))
		return ;
	clean_current(j);
	set_plus(j);
	set_minus(j);
	return ;
}
