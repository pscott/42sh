#include "jobs.h"

/*
**	Find the job with the indicated current char.
*/

t_job	*find_job_by_current(char current)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (j->current == current)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
**	Find the job with the indicated pgid.
*/

t_job	*find_job_by_pgid(pid_t pgid)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
**	Find the job with the indicated job number.
*/

t_job	*find_job_by_number(int num)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (j->num == num)
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
**	Find the job with the indicated job number.
*/

t_job	*find_job_by_command(const char *command)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (ft_strnequ(j->command, command, ft_strlen(command)))
			return (j);
		j = j->next;
	}
	return (NULL);
}

/*
**	Find the job with the indicated job number.
*/

t_job	*find_job_by_subcommand(const char *subcommand)
{
	t_job *j;

	j = g_first_job;
	while (j)
	{
		if (ft_strstr(j->command, subcommand))
			return (j);
		j = j->next;
	}
	return (NULL);
}
