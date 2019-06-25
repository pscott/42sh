#include "jobs.h"

static void		set_plus(t_job *j)
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
			if (!probe->fg)
				res = probe;
			probe = probe->next;
		}
	}
	if (res)
		res->current = '+';
}

static t_job	*check_for_last_job(t_job *j)
{
	t_job	*probe;
	t_job	*last;
	t_job	*res;

	probe = j;
	last = NULL;
	while (probe->next)
	{
		if (!probe->fg)
		{
			res = probe;
			last = res;
		}
		probe = probe->next;
	}
	if (probe && probe->current != '+')
		last = probe;
	return (last);
}

static void		set_minus(t_job *j)
{
	t_job	*res;
	t_job	*last;
	t_job	*probe;

	last = NULL;
	probe = j;
	res = NULL;
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
		last = check_for_last_job(j);
	if (last)
		last->current = '-';
}

static void		clean_current(t_job *j)
{
	while (j)
	{
		j->current = ' ';
		j = j->next;
	}
}

void			set_current(void)
{
	t_job	*j;

	if (!(j = g_first_job))
		return ;
	clean_current(j);
	set_plus(j);
	set_minus(j);
	return ;
}
